
program:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64 
    1004:	48 83 ec 08          	sub    $0x8,%rsp
    1008:	48 8b 05 d9 2f 00 00 	mov    0x2fd9(%rip),%rax        # 3fe8 <__gmon_start__>
    100f:	48 85 c0             	test   %rax,%rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	callq  *%rax
    1016:	48 83 c4 08          	add    $0x8,%rsp
    101a:	c3                   	retq   

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 82 2f 00 00    	pushq  0x2f82(%rip)        # 3fa8 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	f2 ff 25 83 2f 00 00 	bnd jmpq *0x2f83(%rip)        # 3fb0 <_GLOBAL_OFFSET_TABLE_+0x10>
    102d:	0f 1f 00             	nopl   (%rax)
    1030:	f3 0f 1e fa          	endbr64 
    1034:	68 00 00 00 00       	pushq  $0x0
    1039:	f2 e9 e1 ff ff ff    	bnd jmpq 1020 <.plt>
    103f:	90                   	nop
    1040:	f3 0f 1e fa          	endbr64 
    1044:	68 01 00 00 00       	pushq  $0x1
    1049:	f2 e9 d1 ff ff ff    	bnd jmpq 1020 <.plt>
    104f:	90                   	nop
    1050:	f3 0f 1e fa          	endbr64 
    1054:	68 02 00 00 00       	pushq  $0x2
    1059:	f2 e9 c1 ff ff ff    	bnd jmpq 1020 <.plt>
    105f:	90                   	nop
    1060:	f3 0f 1e fa          	endbr64 
    1064:	68 03 00 00 00       	pushq  $0x3
    1069:	f2 e9 b1 ff ff ff    	bnd jmpq 1020 <.plt>
    106f:	90                   	nop

Disassembly of section .plt.got:

0000000000001070 <__cxa_finalize@plt>:
    1070:	f3 0f 1e fa          	endbr64 
    1074:	f2 ff 25 7d 2f 00 00 	bnd jmpq *0x2f7d(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    107b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .plt.sec:

0000000000001080 <__stack_chk_fail@plt>:
    1080:	f3 0f 1e fa          	endbr64 
    1084:	f2 ff 25 2d 2f 00 00 	bnd jmpq *0x2f2d(%rip)        # 3fb8 <__stack_chk_fail@GLIBC_2.4>
    108b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001090 <printf@plt>:
    1090:	f3 0f 1e fa          	endbr64 
    1094:	f2 ff 25 25 2f 00 00 	bnd jmpq *0x2f25(%rip)        # 3fc0 <printf@GLIBC_2.2.5>
    109b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000010a0 <malloc@plt>:
    10a0:	f3 0f 1e fa          	endbr64 
    10a4:	f2 ff 25 1d 2f 00 00 	bnd jmpq *0x2f1d(%rip)        # 3fc8 <malloc@GLIBC_2.2.5>
    10ab:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000010b0 <atoi@plt>:
    10b0:	f3 0f 1e fa          	endbr64 
    10b4:	f2 ff 25 15 2f 00 00 	bnd jmpq *0x2f15(%rip)        # 3fd0 <atoi@GLIBC_2.2.5>
    10bb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .text:

00000000000010c0 <_start>:
    10c0:	f3 0f 1e fa          	endbr64 
    10c4:	31 ed                	xor    %ebp,%ebp
    10c6:	49 89 d1             	mov    %rdx,%r9
    10c9:	5e                   	pop    %rsi
    10ca:	48 89 e2             	mov    %rsp,%rdx
    10cd:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    10d1:	50                   	push   %rax
    10d2:	54                   	push   %rsp
    10d3:	4c 8d 05 e6 02 00 00 	lea    0x2e6(%rip),%r8        # 13c0 <__libc_csu_fini>
    10da:	48 8d 0d 6f 02 00 00 	lea    0x26f(%rip),%rcx        # 1350 <__libc_csu_init>
    10e1:	48 8d 3d 5c 01 00 00 	lea    0x15c(%rip),%rdi        # 1244 <main>
    10e8:	ff 15 f2 2e 00 00    	callq  *0x2ef2(%rip)        # 3fe0 <__libc_start_main@GLIBC_2.2.5>
    10ee:	f4                   	hlt    
    10ef:	90                   	nop

00000000000010f0 <deregister_tm_clones>:
    10f0:	48 8d 3d 31 2f 00 00 	lea    0x2f31(%rip),%rdi        # 4028 <__TMC_END__>
    10f7:	48 8d 05 2a 2f 00 00 	lea    0x2f2a(%rip),%rax        # 4028 <__TMC_END__>
    10fe:	48 39 f8             	cmp    %rdi,%rax
    1101:	74 15                	je     1118 <deregister_tm_clones+0x28>
    1103:	48 8b 05 ce 2e 00 00 	mov    0x2ece(%rip),%rax        # 3fd8 <_ITM_deregisterTMCloneTable>
    110a:	48 85 c0             	test   %rax,%rax
    110d:	74 09                	je     1118 <deregister_tm_clones+0x28>
    110f:	ff e0                	jmpq   *%rax
    1111:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1118:	c3                   	retq   
    1119:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001120 <register_tm_clones>:
    1120:	48 8d 3d 01 2f 00 00 	lea    0x2f01(%rip),%rdi        # 4028 <__TMC_END__>
    1127:	48 8d 35 fa 2e 00 00 	lea    0x2efa(%rip),%rsi        # 4028 <__TMC_END__>
    112e:	48 29 fe             	sub    %rdi,%rsi
    1131:	48 89 f0             	mov    %rsi,%rax
    1134:	48 c1 ee 3f          	shr    $0x3f,%rsi
    1138:	48 c1 f8 03          	sar    $0x3,%rax
    113c:	48 01 c6             	add    %rax,%rsi
    113f:	48 d1 fe             	sar    %rsi
    1142:	74 14                	je     1158 <register_tm_clones+0x38>
    1144:	48 8b 05 a5 2e 00 00 	mov    0x2ea5(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable>
    114b:	48 85 c0             	test   %rax,%rax
    114e:	74 08                	je     1158 <register_tm_clones+0x38>
    1150:	ff e0                	jmpq   *%rax
    1152:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    1158:	c3                   	retq   
    1159:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001160 <__do_global_dtors_aux>:
    1160:	f3 0f 1e fa          	endbr64 
    1164:	80 3d bd 2e 00 00 00 	cmpb   $0x0,0x2ebd(%rip)        # 4028 <__TMC_END__>
    116b:	75 2b                	jne    1198 <__do_global_dtors_aux+0x38>
    116d:	55                   	push   %rbp
    116e:	48 83 3d 82 2e 00 00 	cmpq   $0x0,0x2e82(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    1175:	00 
    1176:	48 89 e5             	mov    %rsp,%rbp
    1179:	74 0c                	je     1187 <__do_global_dtors_aux+0x27>
    117b:	48 8b 3d 86 2e 00 00 	mov    0x2e86(%rip),%rdi        # 4008 <__dso_handle>
    1182:	e8 e9 fe ff ff       	callq  1070 <__cxa_finalize@plt>
    1187:	e8 64 ff ff ff       	callq  10f0 <deregister_tm_clones>
    118c:	c6 05 95 2e 00 00 01 	movb   $0x1,0x2e95(%rip)        # 4028 <__TMC_END__>
    1193:	5d                   	pop    %rbp
    1194:	c3                   	retq   
    1195:	0f 1f 00             	nopl   (%rax)
    1198:	c3                   	retq   
    1199:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000011a0 <frame_dummy>:
    11a0:	f3 0f 1e fa          	endbr64 
    11a4:	e9 77 ff ff ff       	jmpq   1120 <register_tm_clones>

00000000000011a9 <recurse>:
int state;
char *name;
float curr;

int recurse(int it)
{
    11a9:	f3 0f 1e fa          	endbr64 
    11ad:	55                   	push   %rbp
    11ae:	48 89 e5             	mov    %rsp,%rbp
    11b1:	48 83 ec 20          	sub    $0x20,%rsp
    11b5:	89 7d ec             	mov    %edi,-0x14(%rbp)
    11b8:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    11bf:	00 00 
    11c1:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    11c5:	31 c0                	xor    %eax,%eax
    if(it==1) return 1;
    11c7:	83 7d ec 01          	cmpl   $0x1,-0x14(%rbp)
    11cb:	75 07                	jne    11d4 <recurse+0x2b>
    11cd:	b8 01 00 00 00       	mov    $0x1,%eax
    11d2:	eb 5a                	jmp    122e <recurse+0x85>
    int a,b;
    a=it/2; b=3*it+1;
    11d4:	8b 45 ec             	mov    -0x14(%rbp),%eax
    11d7:	89 c2                	mov    %eax,%edx
    11d9:	c1 ea 1f             	shr    $0x1f,%edx
    11dc:	01 d0                	add    %edx,%eax
    11de:	d1 f8                	sar    %eax
    11e0:	89 45 f0             	mov    %eax,-0x10(%rbp)
    11e3:	8b 55 ec             	mov    -0x14(%rbp),%edx
    11e6:	89 d0                	mov    %edx,%eax
    11e8:	01 c0                	add    %eax,%eax
    11ea:	01 d0                	add    %edx,%eax
    11ec:	83 c0 01             	add    $0x1,%eax
    11ef:	89 45 f4             	mov    %eax,-0xc(%rbp)
    printf("add a=%lx, add b=%lx\n", (unsigned long int)&a, (unsigned long int)&b);
    11f2:	48 8d 55 f4          	lea    -0xc(%rbp),%rdx
    11f6:	48 8d 45 f0          	lea    -0x10(%rbp),%rax
    11fa:	48 89 c6             	mov    %rax,%rsi
    11fd:	48 8d 3d 04 0e 00 00 	lea    0xe04(%rip),%rdi        # 2008 <_IO_stdin_used+0x8>
    1204:	b8 00 00 00 00       	mov    $0x0,%eax
    1209:	e8 82 fe ff ff       	callq  1090 <printf@plt>
    if(it%2) return recurse(b);
    120e:	8b 45 ec             	mov    -0x14(%rbp),%eax
    1211:	83 e0 01             	and    $0x1,%eax
    1214:	85 c0                	test   %eax,%eax
    1216:	74 0c                	je     1224 <recurse+0x7b>
    1218:	8b 45 f4             	mov    -0xc(%rbp),%eax
    121b:	89 c7                	mov    %eax,%edi
    121d:	e8 87 ff ff ff       	callq  11a9 <recurse>
    1222:	eb 0a                	jmp    122e <recurse+0x85>
    else return recurse(a);
    1224:	8b 45 f0             	mov    -0x10(%rbp),%eax
    1227:	89 c7                	mov    %eax,%edi
    1229:	e8 7b ff ff ff       	callq  11a9 <recurse>
}
    122e:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
    1232:	64 48 33 0c 25 28 00 	xor    %fs:0x28,%rcx
    1239:	00 00 
    123b:	74 05                	je     1242 <recurse+0x99>
    123d:	e8 3e fe ff ff       	callq  1080 <__stack_chk_fail@plt>
    1242:	c9                   	leaveq 
    1243:	c3                   	retq   

0000000000001244 <main>:

int main(int argc, char const *argv[])
{
    1244:	f3 0f 1e fa          	endbr64 
    1248:	55                   	push   %rbp
    1249:	48 89 e5             	mov    %rsp,%rbp
    124c:	48 83 ec 30          	sub    $0x30,%rsp
    1250:	89 7d dc             	mov    %edi,-0x24(%rbp)
    1253:	48 89 75 d0          	mov    %rsi,-0x30(%rbp)
    char *str1=(char *)malloc(sizeof(char)*10);
    1257:	bf 0a 00 00 00       	mov    $0xa,%edi
    125c:	e8 3f fe ff ff       	callq  10a0 <malloc@plt>
    1261:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
    char *str2=(char *)malloc(sizeof(char)*10);
    1265:	bf 0a 00 00 00       	mov    $0xa,%edi
    126a:	e8 31 fe ff ff       	callq  10a0 <malloc@plt>
    126f:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    printf("_main @ %lx\n",(long unsigned int)&main); 
    1273:	48 8d 05 ca ff ff ff 	lea    -0x36(%rip),%rax        # 1244 <main>
    127a:	48 89 c6             	mov    %rax,%rsi
    127d:	48 8d 3d 9a 0d 00 00 	lea    0xd9a(%rip),%rdi        # 201e <_IO_stdin_used+0x1e>
    1284:	b8 00 00 00 00       	mov    $0x0,%eax
    1289:	e8 02 fe ff ff       	callq  1090 <printf@plt>
    printf("PI,MOD,evenPrime,UNLUCKy @ %lx %lx %lx %lx\n",(long unsigned int)&PI,(long unsigned int)&MOD,(long unsigned int)&evenPrime,(long unsigned int)&UNLUCKY);
    128e:	48 8d 35 8f 2d 00 00 	lea    0x2d8f(%rip),%rsi        # 4024 <UNLUCKY>
    1295:	48 8d 0d 84 2d 00 00 	lea    0x2d84(%rip),%rcx        # 4020 <evenPrime>
    129c:	48 8d 15 75 2d 00 00 	lea    0x2d75(%rip),%rdx        # 4018 <MOD>
    12a3:	48 8d 05 66 2d 00 00 	lea    0x2d66(%rip),%rax        # 4010 <PI>
    12aa:	49 89 f0             	mov    %rsi,%r8
    12ad:	48 89 c6             	mov    %rax,%rsi
    12b0:	48 8d 3d 79 0d 00 00 	lea    0xd79(%rip),%rdi        # 2030 <_IO_stdin_used+0x30>
    12b7:	b8 00 00 00 00       	mov    $0x0,%eax
    12bc:	e8 cf fd ff ff       	callq  1090 <printf@plt>
    printf("state,name,curr @ %lx %lx %lx\n",(long unsigned int)&state,(long unsigned int)&name,(long unsigned int)&curr); 
    12c1:	48 8d 0d 78 2d 00 00 	lea    0x2d78(%rip),%rcx        # 4040 <curr>
    12c8:	48 8d 15 69 2d 00 00 	lea    0x2d69(%rip),%rdx        # 4038 <name>
    12cf:	48 8d 05 5a 2d 00 00 	lea    0x2d5a(%rip),%rax        # 4030 <state>
    12d6:	48 89 c6             	mov    %rax,%rsi
    12d9:	48 8d 3d 80 0d 00 00 	lea    0xd80(%rip),%rdi        # 2060 <_IO_stdin_used+0x60>
    12e0:	b8 00 00 00 00       	mov    $0x0,%eax
    12e5:	e8 a6 fd ff ff       	callq  1090 <printf@plt>

    printf("_recurse @ %lx\n",(long unsigned int)&recurse); 
    12ea:	48 8d 05 b8 fe ff ff 	lea    -0x148(%rip),%rax        # 11a9 <recurse>
    12f1:	48 89 c6             	mov    %rax,%rsi
    12f4:	48 8d 3d 84 0d 00 00 	lea    0xd84(%rip),%rdi        # 207f <_IO_stdin_used+0x7f>
    12fb:	b8 00 00 00 00       	mov    $0x0,%eax
    1300:	e8 8b fd ff ff       	callq  1090 <printf@plt>
    //printf("Argc= %d\n", argc);

    if(argc!=2) return 1;
    1305:	83 7d dc 02          	cmpl   $0x2,-0x24(%rbp)
    1309:	74 07                	je     1312 <main+0xce>
    130b:	b8 01 00 00 00       	mov    $0x1,%eax
    1310:	eb 38                	jmp    134a <main+0x106>
    else 
    {
        int a=atoi(argv[1]);
    1312:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
    1316:	48 83 c0 08          	add    $0x8,%rax
    131a:	48 8b 00             	mov    (%rax),%rax
    131d:	48 89 c7             	mov    %rax,%rdi
    1320:	e8 8b fd ff ff       	callq  10b0 <atoi@plt>
    1325:	89 45 ec             	mov    %eax,-0x14(%rbp)
        printf("Converged to: %d\n",recurse(a));
    1328:	8b 45 ec             	mov    -0x14(%rbp),%eax
    132b:	89 c7                	mov    %eax,%edi
    132d:	e8 77 fe ff ff       	callq  11a9 <recurse>
    1332:	89 c6                	mov    %eax,%esi
    1334:	48 8d 3d 54 0d 00 00 	lea    0xd54(%rip),%rdi        # 208f <_IO_stdin_used+0x8f>
    133b:	b8 00 00 00 00       	mov    $0x0,%eax
    1340:	e8 4b fd ff ff       	callq  1090 <printf@plt>
    }
    return 0;
    1345:	b8 00 00 00 00       	mov    $0x0,%eax
}
    134a:	c9                   	leaveq 
    134b:	c3                   	retq   
    134c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000001350 <__libc_csu_init>:
    1350:	f3 0f 1e fa          	endbr64 
    1354:	41 57                	push   %r15
    1356:	4c 8d 3d 43 2a 00 00 	lea    0x2a43(%rip),%r15        # 3da0 <__frame_dummy_init_array_entry>
    135d:	41 56                	push   %r14
    135f:	49 89 d6             	mov    %rdx,%r14
    1362:	41 55                	push   %r13
    1364:	49 89 f5             	mov    %rsi,%r13
    1367:	41 54                	push   %r12
    1369:	41 89 fc             	mov    %edi,%r12d
    136c:	55                   	push   %rbp
    136d:	48 8d 2d 34 2a 00 00 	lea    0x2a34(%rip),%rbp        # 3da8 <__do_global_dtors_aux_fini_array_entry>
    1374:	53                   	push   %rbx
    1375:	4c 29 fd             	sub    %r15,%rbp
    1378:	48 83 ec 08          	sub    $0x8,%rsp
    137c:	e8 7f fc ff ff       	callq  1000 <_init>
    1381:	48 c1 fd 03          	sar    $0x3,%rbp
    1385:	74 1f                	je     13a6 <__libc_csu_init+0x56>
    1387:	31 db                	xor    %ebx,%ebx
    1389:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1390:	4c 89 f2             	mov    %r14,%rdx
    1393:	4c 89 ee             	mov    %r13,%rsi
    1396:	44 89 e7             	mov    %r12d,%edi
    1399:	41 ff 14 df          	callq  *(%r15,%rbx,8)
    139d:	48 83 c3 01          	add    $0x1,%rbx
    13a1:	48 39 dd             	cmp    %rbx,%rbp
    13a4:	75 ea                	jne    1390 <__libc_csu_init+0x40>
    13a6:	48 83 c4 08          	add    $0x8,%rsp
    13aa:	5b                   	pop    %rbx
    13ab:	5d                   	pop    %rbp
    13ac:	41 5c                	pop    %r12
    13ae:	41 5d                	pop    %r13
    13b0:	41 5e                	pop    %r14
    13b2:	41 5f                	pop    %r15
    13b4:	c3                   	retq   
    13b5:	66 66 2e 0f 1f 84 00 	data16 nopw %cs:0x0(%rax,%rax,1)
    13bc:	00 00 00 00 

00000000000013c0 <__libc_csu_fini>:
    13c0:	f3 0f 1e fa          	endbr64 
    13c4:	c3                   	retq   

Disassembly of section .fini:

00000000000013c8 <_fini>:
    13c8:	f3 0f 1e fa          	endbr64 
    13cc:	48 83 ec 08          	sub    $0x8,%rsp
    13d0:	48 83 c4 08          	add    $0x8,%rsp
    13d4:	c3                   	retq   
