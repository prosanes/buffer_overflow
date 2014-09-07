O objetivo dessa prática é explorar uma vulnerabilidade em um programa, fazendo com que o sistema abra um shell de root.

# sysctl -w kernel.randomize_va_space=0
desativa a proteção do kernel que randomiza o endereço da pilha de execução.

-----------------------
Parte1: *Mostrar a pilha*
gcc parte1.c -fno-stack-protector -z execstack -o parte1 -O0

gdb parte1
disassemble main -> mostrar chamada da função e passagem do argumento. Anotar endereço de retorno.
break funcao; run
disassemble funcao -> mostrar como salva ebp e como abre espaço para as variáveis na pilha.
x/64b|x $esp -> exibe a pilha. Procurar endereço de retorno, anotado anteriormente, mostrar as coisas empilhadas.

----------------------
Parte2: *Alterar curso de execução, para uma função já existente no programa*
Mostrar o fonte do programa vulneravel e porque é vulneravel. Explicar os passos para alterar o endereço de retorno para
a funcao print_overflow().
gcc vulneravel.c -fno-stack-protector -z execstack -O0 -o vulneravel
gdb vulneravel
disassemble main -> anotar endereço de retorno da bof.
p print_overflow -> anotar endereço da função print_overflow.
break bof; run
x/64b|x $esp -> exibe a pilha. Procurar posição endereço de retorno anotado anteriormente.

Mostrar fonte exploit.c e inserir o endereço de print_overflow.
gcc exploit.c -o exploit
./exploit
od -t x2 badfile

gdb vulneravel
disassemble main -> anotar endereço de retorno para procurar na pilha.
break bof; run
disassemble bof
x/64b|x $esp -> exibir a pilha antes de carregar o badfile
ni 13 -> executar até o arquivo ser carregado.
x/64b|x $esp -> mostrar os nops, verificar onde é o começo do buffer e calcular a posição do endereço de retorno
relativo ao início do buffer.
quit

Alterar o exploit.c com a nova posição do endereço de retorno.
gcc exploit.c -o exploit
./exploit
./vulneravel

------------------------
Parte3: *Inserir shellcode, e alterar curso de execução para o shellcode* 
        (Não utiliza NOP slide, logo só funciona no gdb)
Mostrar o fonte do novo vulneravel.c sem a função print_overflow. Explicar que vamos inserir um código no programa.
Mostrar o fonte do exploit.c, inserindo o shellcode e memcpy.
gcc vulneravel.c -fno-stack-protector -z execstack -O0 -o vulneravel
gcc exploit.c -o exploit
./exploit
od -t x2 badfile -> mostrar o shellcode e a posição onde devemos inserir o endereço de retorno para apontar para o
shellcode que vai estar logo em seguida.

gdb vulneravel
break bof; run
disassemble main -> anotar endereço de retorno.
x/64b|x $esp -> exibir a pilha antes de carregar o badfile.
disassemble bof
ni 13
x/64b|x $esp -> mostrar que o aa está no lugar certo e copiar o endereço onde o shellcode começa.
alterar exploit.c colocando o endereço de desvio certo

-------------------------
parte4: *Usar NOP slide*

Mostrar o fonte do vulneravel.c. Igual ao anterior
Mostrar o fonte do exploit.c, chutar um valor de retorno, e botar o shellcode no final do buffer.

gcc vulneravel.c -fno-stack-protector -z execstack -O0 -o vulneravel
gcc exploit.c -o exploit
./exploit
od -t x2 badfile -> mostrar o shellcode e a posição onde devemos inserir o endereço de retorno para apontar para o
algum lugar antes do shellcode. 

./vulneravel

--------------------
parte5: *return to libc*

Mostrar o fonte do vulneravel.c. Igual ao anterior

Precisamos achar o endereço da função system(), a qual usaremos para abrir um shell. Portanto, criamos um programa para
isso.
Mostrar o fonte do end-system.c.
gcc end-system.c -o end-system
gdb end-system
break main
run
p system -> Anotar endereço de system
p exit > Anotar endereço de system

Precisamos utilizar '/bin/bash' como parametro para system(). Usaremos a string que está na variável de ambiente MYSHELL.
$export MYSHELL=/bin/sh|/bin/bash
$env
Para achar essa variável de ambiente, utilizamos o programa end-env-var.c
Mostrar o fonte de end-env-var.c
gcc end-env-var.c
./end-env-var
Teremos um endereço proximo a '/bin/bash'. Porém este endereço muda dependendo do programa.
Utilizaremos o gdb mais tarde para tentar achar essa string no programa vulneravel.

Mostrar fonte de exploit.c
gcc exploit.c -o exploit
od -t x2 badfile

Achar valores relativos de retorno.
gcc vulneravel.c -fno-stack-protector -o vulneravel
gdb vulneravel
b bof
run
disassamble main -> Descobrir endereço de retorno
x/64x $esp -> Achar endereço de retorno
ni 7 -> executar até carregar buffer na memoria
x/64x $esp -> Descobrir local do endereço de retorno em relação ao buffer

Voltar no exploit.c e inserir o endereco de system() no buffer
Inserir o endereço de retorno para exit() logo apos system().
Inserir endereço de SHELL ('/bin/bash') que sera usado como argumento de system
gcc exploit.c -o exploit
./exploit

./vulneravel
Provavelmente, o programa fechou, sem erro, mas não abriu um shell.

$env -> Mostra todas as variaveis de ambiente, para termos uma nocao na hora de debugar vulneravel
./end-env-var -> para relembrar aonde está a envvar MYSHELL +-
gdb vulneravel
b main
run
x/s 0x(endereco obtido a cima)

ir modificando exploit, de acordo com os endereços achados a cima.


-------------------
set-root-uid -> Quando um programa tem o atributo set-uid habilitado ele é executado com os privilégios do dono do
arquivo. Ou seja, se o dono do arquivo é o usuário root, qualquer usuário que executar aquele programa, terá privilégios
de root durante a execução.

Ao compilar o programa que desejamos explorar, precisamos desligar o mecanismo de proteção do gcc chamado "Stack Guard".
Essa proteção funciona colocando no começo de cada pilha de chamada de função uma "Canary Word". Assim, toda vez que a
função acaba, antes de retornar para a função que a chamou, verifica-se a "Canary Word". Como ela fica entre as
variáveis locais e o endereço de retorno, se um buffer overflow ocorrer e substituir o endereço de retorno, também
substituirá a "Canary Word" causando uma falha na execução do programa.
