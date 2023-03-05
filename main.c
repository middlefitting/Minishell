#include <stdio.h>
#include <dirent.h>
#include <term.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

void	init_tflag(struct termios *t);
void	init_cc(struct termios *t);
void	handler(int sig);

//메인에서 실행부까지 전달해야 하는 멤버
//termios 구조체 - 부모프로세스 (메인)과 자식프로세스간 옵션을 다르게 설정해야할수도 있어서
//signal handler - 상호작용하는 부모프로세스의 경우 전달받는 signal의 역할이 명령실행(자식)시 전달받는
//signal의 역할과 다르기때문
//envp - 실행부에서 환경변수를 통해서 execve를 실행하기때문

int main (int argc, char *argv[], char **envp)
{
	struct termios t;
	char *str;
	int check;

	if (tcgetattr (STDIN_FILENO, &t) == -1) // 상호작용하려는 대상 (첫번째 인자)의 속성값을 가져와 연결
		return (1);
	init_tflag (&t); //bash가 설정한 터미널 값을 원하는 값으로 초기화 (현재 echoctl만 꺼놓음)
	if (tcsetattr(STDIN_FILENO, TCSANOW, &t) == -1) //바뀐값을 바로 적용하는 함수
		return (1);
	if (tgetent (NULL, "xterm-256color") == -1) // 현재 bash의 TERM환경변수 값을 가져옴.
		return (1);
	signal (SIGINT, handler); //ctrl-c 입력시 새로운 프롬프트 출력
	signal (SIGQUIT, SIG_IGN); //ctrl-\ 입력시 무시

	while (1)
	{
		str = readline ("minishell$ "); //minishell$ 출력후 입력받은 문자열을 str에 저장
		if (str == NULL)
		{
			write (1, "exit\n", 5); //ctrl-d 입력시 exit 출력후 쉘 종료
			exit (0);
		}
		add_history (str);
		if (!strcmp (str, "exit")) //입력받은 문자열이 exit일 경우 종료 (ft_strcmp로 수정필요)
		{
			write (1, "exit\n", 5);
			exit (0);
		}
		free (str); //전달받은 문자열 malloc으로 할당했기때문에 free. 할당실패시 예외처리 추후 추가필요
	}
	return (0);
}

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0); //redisplay 호출시 현재 입력중인 문자열을 출력하기 때문에, 현재 문자열 ""로 대체
		write (1, "\n", 1); //ctrl-c입력시 다음줄에 프롬프트 출력하기 때문
		rl_on_new_line(); //커서를 이동시켜주는 함수
		rl_redisplay(); //프롬프트 출력
	}
	return ;
}

void	init_tflag(struct termios *t)
{
	t->c_lflag &= ~ECHOCTL;//제어문자 입력받았을때 해당 제어문자 출력하는 옵션 (옵션 꺼짐)
	//t.c_lflag &= ICANON; //ICANON = 문자열을 입력받을건지 or 한문자씩 입력받을건지 (나중에 필요할수도?)
	//init_cc (t); 제어문자 설정함수, 기본적으로 bash옵션을 적용
}

void	init_cc(struct termios *t)
{
	t->c_cc[VDISCARD] =0xf;
	t->c_cc[VDSUSP] = 0x19;
	t->c_cc[VEOF] = 0x04;
	t->c_cc[VERASE] = 0x7F;
	t->c_cc[VINTR] = 0x3;
	t->c_cc[VKILL] = 0x15;
	t->c_cc[VLNEXT] = 0x16;
	t->c_cc[VMIN] = 1;
	t->c_cc[VQUIT] = 0x1c;
	t->c_cc[VREPRINT] = 0x12;
	t->c_cc[VSTART] = 0x11;
	t->c_cc[VSTATUS] = 0x14;
	t->c_cc[VSTOP] = 0x13;
	t->c_cc[VSUSP] = 0x1a;
	t->c_cc[VWERASE] = 0x17;
	t->c_cc[VTIME] = 0;
}