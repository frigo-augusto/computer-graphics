/*********************************************************************
// Classe para gerenciamento de transformacoes, contem os metodos de manipulacao de transformacoes.
// *********************************************************************/

#include "TransformationManager.h"
#include "../gl_canvas2d.h"
#include "../buttons/TransformButton.h" //remover isso depois

#define MATRIX_SIZE 2
#define BACKSPACE 8
#define MATX 275
#define MATY 500
#define SIZEX 150
#define SIZEY 100

#include "../WritableElement.h"

TransformationManager::TransformationManager(FigureManager *_figureManager)
{
   currentMatrix = new WritableMatrix(MATRIX_SIZE, MATRIX_SIZE, MATX, MATY, SIZEX, SIZEY); // inicializa a matriz em que serao escritos os valores da mat de transformacao
   figureManager = _figureManager;
}

TransformationManager::~TransformationManager()
{
   delete currentMatrix;
}

// adiciona os valores da matriz a pilha de transformacao
void TransformationManager::addMatrixToStack()
{
   Matrix *m = new Matrix(MATRIX_SIZE, MATRIX_SIZE);
   for (int i = 0; i < MATRIX_SIZE; i++)
   {
      for (int j = 0; j < MATRIX_SIZE; j++)
      {
         m->getMainMatrix()[i][j] = currentMatrix->getMainMatrix()[i][j]->getValue();
      }
   }
   delete currentMatrix; // dando segfault
   transformationStack.push(m);
   currentMatrix = new WritableMatrix(MATRIX_SIZE, MATRIX_SIZE, MATX, MATY, SIZEX, SIZEY);
}

// gera a matriz de transformacao com base nas matrizes inseridas pelo usuario.
// as transformacoes serao aplicadas na ordem inversa da inserida pelo usuario, permitindo que ele insira
//  as matrizes na ordem em que quer transformar.
void TransformationManager::endTransform()
{
   if (transformationStack.empty())
      return;

   Matrix *resultMatrix = new Matrix(transformationStack.top()->lines, transformationStack.top()->columns);
   Matrix *temp;
   while (!transformationStack.empty())
   {
      Matrix *currentMatrix = transformationStack.top();
      transformationStack.pop();
      temp = (*resultMatrix) * (*currentMatrix);
      delete resultMatrix;
      delete currentMatrix;
      resultMatrix = temp;
   }
   if (!figureManager->figures.empty() && figureManager->figures.back()->selected)
   {
      figureManager->figures.back()->transform(*resultMatrix);
   }
}

void TransformationManager::render()
{
   for (int i = 0; i < MATRIX_SIZE; i++)
   {
      for (int j = 0; j < MATRIX_SIZE; j++)
      {
         currentMatrix->getMainMatrix()[i][j]->render();
      }
   }
}

void TransformationManager::checkCollision(int mx, int my, int state, int *gbli, int *gblj)
{
   for (int i = 0; i < MATRIX_SIZE; i++)
   {
      for (int j = 0; j < MATRIX_SIZE; j++)
      {
         if (currentMatrix->getMainMatrix()[i][j]->checkCollision(mx, my) && state == 0)
         {
            *gbli = i;
            *gblj = j; // indice da matriz que sera acessado no proximo input do teclado
            return;
         }
      }
   }
   if (state == 0)
   { // clicou fora do botao, unselect
      *gbli = -1, *gblj = -1;
   }
}

/*
 * Verifica se o usuario digitou algo, e retorna se ele esta atualmente digitando
 * nesse campo ou nao.
 */
bool TransformationManager::checkWrite(int i, int j, int key)
{
   if (i == -1 || j == -1)
      return false; // usuario nao esta digitando
   if (key == BACKSPACE)
   {
      currentMatrix->getMainMatrix()[i][j]->removeLastCharacter();
   }
   else
   {
      currentMatrix->getMainMatrix()[i][j]->addCharacter(key);
   }
   return true; // usuario esta digitando
}
