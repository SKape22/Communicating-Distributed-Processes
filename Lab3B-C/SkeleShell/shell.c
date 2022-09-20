#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>
#include <limits.h>
#include <grp.h>
#include <pwd.h>
#include "tokenizer.h"

/* Convenience macro to silence compiler warnings about unused function parameters. */
#define unused __attribute__((unused))

/* Whether the shell is connected to an actual terminal or not. */
bool shell_is_interactive;

/* File descriptor for the shell input */
int shell_terminal;

/* Terminal mode settings for the shell */
struct termios shell_tmodes;

/* Process group id for the shell */
pid_t shell_pgid;

FILE *FDOUT=NULL;
int STDOUT;

static int line_num=0;

int cmd_exit(struct tokens *tokens);
int cmd_help(struct tokens *tokens);
int cmd_id(struct tokens *tokens);
int cmd_reset(struct tokens *tokens);
/* Built-in command functions take token array and return int */
typedef int cmd_fun_t(struct tokens *tokens);

/* Built-in command struct and lookup table */
typedef struct fun_desc {
  cmd_fun_t *fun;
  char *cmd;
  char *doc;
} fun_desc_t;

int isValidProcess(char *processpath)
{
  return access(processpath,F_OK);
}

fun_desc_t cmd_table[] = {
  {cmd_help, "?", "show this help menu"},
  {cmd_exit, "exit", "exit the command shell"},
  {cmd_id, "id", "shows the user id, arguments \n\t -u \n\t\tprint only the effective user ID \n\t -g \n\t\tprint only the effective group ID  \n\t -G \n\t\tprint all group IDs"},
  {cmd_reset, "reset", "clears output and resets history"}
};

char **extract_argv(unused struct tokens* tokens)
{
    int argc = tokens_get_length(tokens);
    char **argv=(char **)malloc(sizeof(char *)*(argc+1));
    int i=0;
    int offset=0;
    for (i = 0; i < argc; i++) {
      if(!strcmp(tokens_get_token(tokens,i),">"))
      {
        if(i<argc-1)
        {
          i++; offset+=2;
        }
        else 
        {
          i++;
          offset++;
        }
      }
      else
      {
        argv[i-offset] = tokens_get_token(tokens, i);
      }
    }
    argv[i-offset]=NULL;
    return argv;
}

FILE* set_stream(char *fname, int target)
{
    //printf("File open started\n");

    FILE *fp=fopen(fname,"w");

    if(!fp) return NULL;
    int fno=fileno(fp);

    dup2(fno,target);

    return fp;
} //working fine tested ok

void set_token_stream(unused struct tokens *tokens)
{
  int n=tokens_get_length(tokens);
  for(int i=0; i<n; i++)
  {
    if(!strcmp(tokens_get_token(tokens,i),">"))
    {
      if(i+1>=n)
      {
        printf("No output file specified!\n");
        return;
      }
      char *fname=tokens_get_token(tokens,++i);
      //printf("%s\n",fname);
      FDOUT=set_stream(fname,STDOUT_FILENO);
      if(FDOUT==NULL) printf("Cannot Open file");
      //printf("Processs shisfting done");
      return;
    }
  }
}

int cmd_reset(unused struct tokens* tokens)
{
  
  system("clear");
  line_num=0;
  return 1;
}

void print_grps()
{
  struct passwd* user;
    int nGroups = 20;
    gid_t* groups;
    groups = malloc(nGroups * sizeof(gid_t));
    struct group* gr;
    while(user = getpwent()){
        nGroups = 20;
        getgrouplist(user->pw_name, user->pw_gid, groups, &nGroups);
        int i;
        for(i = 0; i < nGroups; ++i){
            gr = getgrgid(groups[i]);
            if(gr){
                printf("%s (%d)", gr->gr_name,gr->gr_gid);

            }  
        }
        printf("\n");
    }

    free(groups);
}

int cmd_id(unused struct tokens *tokens)
{
  // pid_t child_pid;

  // if ((child_pid = fork()) == 0) {

  //   char **argv=extract_argv(tokens);
  //   execvp("/usr/bin/id", argv);

  //   fprintf(stderr, "Error Ocuured While Executing Command\n");
  //   exit(1);
  // }
  // wait(NULL);

  // gid_t gid;
  // gid=getgid();
  // struct group *g;
  // g = getgrgid(gid);
  // //getgr
  // if(g!=NULL)
  // for(int i=0; g->gr_mem[i]!=NULL; i++)
  // {
  //    printf("%s, ",g->gr_mem[i]);
  // }
  // while(*g->gr_mem)
  // {
  //   (g->gr_mem)++;
  // }
  print_grps();
  // printf("%s gr_name\n",g->gr_name);
  // printf("%s gr_passwd\n",g->gr_passwd);
  // printf("%d g_gid\n",g->gr_gid);

  // printf("%d getgid\n",getgid());
  // printf("%d getuid\n",getuid());
  // //free(g);
  return 1;
}

int cmd_custom(unused struct tokens* tokens)
{
  pid_t child_pid;

  if ((child_pid = fork()) == 0) {

    char **argv=extract_argv(tokens);
    execvp(tokens_get_token(tokens,0), argv);

    fprintf(stderr, "Error Ocuured While Executing Command\n");
    exit(1);
  }
  wait(NULL);
  return 1;
}

/* Prints a helpful description for the given command */
int cmd_help(unused struct tokens *tokens) {
  for (unsigned int i = 0; i < sizeof(cmd_table) / sizeof(fun_desc_t); i++)
    printf("%s - %s\n", cmd_table[i].cmd, cmd_table[i].doc);
  return 1;
}

/* Exits this shell */
int cmd_exit(unused struct tokens *tokens) {
  exit(0);
}

/* Looks up the built-in command, if it exists. */
int lookup(char cmd[]) {
  for (unsigned int i = 0; i < sizeof(cmd_table) / sizeof(fun_desc_t); i++)
    if (cmd && (strcmp(cmd_table[i].cmd, cmd) == 0))
      return i;
  return -1;
}

/* Intialization procedures for this shell */
void init_shell() {
  /* Our shell is connected to standard input. */
  shell_terminal = STDIN_FILENO;

  /* Check if we are running interactively */
  shell_is_interactive = isatty(shell_terminal);

  if (shell_is_interactive) {
    /* If the shell is not currently in the foreground, we must pause the shell until it becomes a
     * foreground process. We use SIGTTIN to pause the shell. When the shell gets moved to the
     * foreground, we'll receive a SIGCONT. */
    while (tcgetpgrp(shell_terminal) != (shell_pgid = getpgrp()))
      kill(-shell_pgid, SIGTTIN);

    /* Saves the shell's process id */
    shell_pgid = getpid();

    /* Take control of the terminal */
    tcsetpgrp(shell_terminal, shell_pgid);

    /* Save the current termios to a variable, so it can be restored later. */
    tcgetattr(shell_terminal, &shell_tmodes);
  }
}

void terminal_prefix(int line_num)
{
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    fprintf(stdout, "\033[0;32mpushkar@CDP\033[0;33m[%d]\033[0;34m%s\n: $ \033[0;37m", line_num,cwd);
}

int main(unused int argc, unused char *argv[]) {
  init_shell();
  STDOUT=dup(1);

  static char line[4096];
  //static int line_num = 0;

  /* Please only print shell prompts when standard input is not a tty */
  if (shell_is_interactive)
      terminal_prefix(line_num++);
  while (fgets(line, 4096, stdin)) {
    /* Split our line into words. */
    struct tokens *tokens = tokenize(line);
    
    set_token_stream(tokens); // set the token stream

    /* Find which built-in function to run. */
    int fundex = lookup(tokens_get_token(tokens, 0));

    if (fundex >= 0) {
      cmd_table[fundex].fun(tokens);
    } else {

      // if(isValidProcess(tokens_get_token(tokens,0))<0)
      // /* REPLACE this to run commands as programs. */
      // fprintf(stdout, "This shell doesn't know how to run programs.\n");

      cmd_custom(tokens);
    }
    dup2(STDOUT,1); // redirect back to stdout

    if (shell_is_interactive)
      /* Please only print shell prompts when standard input is not a tty */
      terminal_prefix(line_num++);

    /* Clean up memory */
    tokens_destroy(tokens);
    if(FDOUT!=NULL) fclose(FDOUT);
    FDOUT=NULL;
  }

  return 0;
}
