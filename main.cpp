#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

bool sair = 0;

const GLfloat tam_x = 30.0f; // raio total
const GLfloat tam_y = 30.0f;
const GLfloat tam_x1 = 19.0f; // minutos
const GLfloat tam_x2 = 17.0f; // horas
const GLfloat tam_x3 = 2.0f; //eixo

const GLint sy = 19;
const GLint my = 17;
const GLint hy = 13;

int x = 0, y = 0;

int hora;
int minuto;
int segundo;
float s_angulo, m_angulo, h_angulo;

static void Atualiza_tamanho(int largura, int altura)
{

    glViewport(0,0,largura,altura);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-30.0,30.0,-30.0,30.0);
    /*
    // Redimensiona a viewport para ficar com o mesmo tamanho da janela
    glViewport(0, 0, largura, altura);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Faz o mapeamento entre a viewport e o sistema de coordenadas 2D
    // levando em consideracao a relacao entre a largura e a altura da viewport
    // Nesse caso, o objeto renderizado vai mudar de tamanho conforme a janela
    // aumentar ou diminuir
    if (largura <= altura)
    {
       gluOrtho2D(-tam_x, tam_x, -tam_y * altura / largura, tam_y * altura / largura);
    }
    else
    {
       gluOrtho2D(-tam_x * largura / altura, tam_x * largura / altura, -tam_y, tam_y);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    */
}

void Teclado(unsigned char tecla, int x, int y)
{
	switch (tecla)
	{
		case 27 :
		case 'q' :
			sair = 1;
			exit(0);
		break;
	}
}

void pontHor()
{
	//PONTEIRO HORAS  ##########################################################################
	glLineWidth(4);
	glBegin(GL_LINES);
	glColor3f(0.6f, 0.7f, 0.0f); //cor amarelo
	glVertex2f(0,0);
	glVertex2f(x + (cos(h_angulo) * hy), y + (sin(h_angulo) * hy));

	glEnd();
}

static void pontMin()
{
	// PONTEIRO MINUTOS ##########################################################################
	glLineWidth(4);
	glBegin(GL_LINES);
	glColor3f(0.6f, 0.7f, 0.0f); //cor amarelo
	glVertex2f(0,0);
	glVertex2f(x + (cos(m_angulo) * my), y + (sin(m_angulo) * my));
	glEnd();
}

static void pontSeg()
{
	//PONTEIRO SEGUNDOS  ##########################################################################
	glLineWidth(1);
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f); //cor vermelho
	glVertex2f(0, 0);
	glVertex2f(x + (cos(s_angulo) * sy), y + (sin(s_angulo) * sy));

	glEnd();
}


// FUNÇÃO QUE DESENHA O RELOGIO ##########################################################################
void desenharRelogio()
{
	int cont;// DIFERENÇA DE HORAS PARA GRAUS DE HORAS - 3:15:900
	int x = 0, y = 0, num_linhas = 12;
	float raio = 20.0, angulo;

	time_t seg;
	time (&seg);
	struct tm *h_atual{};
	h_atual = localtime(&seg);// h_atual->tm_hour, ->tm_min, ->tm_sec


	s_angulo = ((((segundo - 15) * 2) * M_PI) / 60) * -1;
	m_angulo = (((minuto -15) * 2 * M_PI)/60)* -1;
	h_angulo = (((hora - 3 )  * 2 * M_PI)/12) * -1;


	//CRIAR MARCA DAS HORAS  ##########################################################################
	glLineWidth(4);
	glBegin(GL_LINES);
	for(int i = 0; i < num_linhas; i++)
		{
			raio = 20;
			glColor3f(1.0f, 1.0f, 1.0f); //cor branco
			angulo = i * 2 * M_PI / num_linhas;
			glVertex2f(x + (cos(angulo) * raio), y + (sin(angulo) * raio));
			raio = 17;
			glVertex2f(x + (cos(angulo) * raio), y + (sin(angulo) * raio));
		}

	glEnd();

	// CRIAR MARCA DOS MINUTOS  ##########################################################################
	glLineWidth(4);
	num_linhas = num_linhas * 5;
	glBegin(GL_LINES);

	for(int i = 0; i < num_linhas; i++)
		{
			raio = 20.0;
			glColor3f(1.0f, 1.0f, 1.0f); //cor branco
			angulo = i * 2 * M_PI / num_linhas;
			glVertex2f(x + (cos(angulo) * raio), y + (sin(angulo) * raio));
			raio = 19;
			glVertex2f(x + (cos(angulo) * raio), y + (sin(angulo) * raio));
		}

	glEnd();

	// EIXO DOS PONTEIROS  ##########################################################################
	glBegin(GL_QUAD_STRIP);
	x = 0;
	y = 0;
	float rai = 0.01;
	num_linhas = num_linhas * 6;
	for(int i = 0; i < num_linhas; i++)
		{

			glVertex2f(x + (cos(angulo) * rai), y + (sin(angulo) * rai));
			raio = 2.0;
			glColor3f(0.6f, 0.7f, 0.0f); //cor amarelo
			angulo = i * 2 * M_PI / num_linhas;
			glVertex2f(x + (cos(angulo) * raio), y + (sin(angulo) * raio));
		}
	glEnd();

	glLoadIdentity();
	glRotatef(s_angulo,0.0,0.0,1.0);
	pontSeg();
	printf("\nhora....%d",h_atual->tm_hour );
	printf("\n\nminuto....%d",h_atual->tm_min );
	printf("\nsegundo....%d",h_atual->tm_sec );

  	glLoadIdentity();

	glRotatef(m_angulo,0,0,1.0);
	pontMin();
	printf("\n\nhora....%d",h_atual->tm_hour );
 	printf("\n\nminuto....%d",h_atual->tm_min );
	printf("\nsegundo....%d",h_atual->tm_sec );


   	glLoadIdentity();
	glRotatef(h_angulo,0,0,1.0);
	pontHor();
	printf("\nhora....%d",h_atual->tm_hour );
   	printf("\n\nminuto....%d",h_atual->tm_min );
    printf("\nsegundo....%d",h_atual->tm_sec );

    glLoadIdentity();
    glFlush();


}

void move(int n)
{
     // Apos a execucao desse trecho a estrutura "datahora"
     // tera armazenada a data/hora atual do relogio da maquina
     time_t agora = time(0);
     struct tm *datahora = localtime(&agora);

     hora = datahora->tm_hour;
     minuto = datahora->tm_min;
     segundo = datahora->tm_sec;

     glutPostRedisplay(); // Pede para redesenhar a tela. Vai chamar a funcao desenha()
     glutTimerFunc(1000, move, 0);     // Pede para chamar de novo a funcao move
}

static void Atualiza_desenho(void)
{

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();//inicializa matriz com a matriz identidade
    glClear(GL_COLOR_BUFFER_BIT);//Limpa janela
    glColor3f(0.0,0.0,0.0);

    desenharRelogio(); // chama função que desenha relogio na matriz

    glFlush();
}

int main(int argc, char **argv)
{
	int cont;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE );
    glutInitWindowPosition(500,200);
    glutInitWindowSize(600,600);
    glutCreateWindow("GL - Relogio Lucas Matheus");
    //registra fun��o callback para tratar evento de redimensionamento de janela
    glutDisplayFunc(Atualiza_desenho);
    //define a cor de limpeza da janela como sendo a branca
    glutReshapeFunc(Atualiza_tamanho);
    //registra fun��o callback para tratar evento de desenho
    glutTimerFunc(1000, move, 0);
    glClearColor(0,0,0,0);
    //Inicia tratamento de eventos

    glutMainLoop();


    return 0;
}
