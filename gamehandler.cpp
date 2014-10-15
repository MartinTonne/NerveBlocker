#include "gamehandler.h"
#include <QDebug>
#include <QImage>
#include <QFileInfo>
#include <cstdlib>



GameHandler::GameHandler(QObject *parent) :
    QObject(parent){
    m_task = (rand() % MAX_IMAGES)+1;
    m_image = QString("/gameImages/%1a.png").arg(m_task);
    m_question = "Where is the femoral nerve?";
    m_answer = "";
    m_taskActive = true;
    m_points = 0;
    m_multiplier = 1;
    m_tasks_finished = 0;
}

void GameHandler::newTask(){
    m_task = (rand() % MAX_IMAGES)+1;
    setAnswer("");
    setImage(QString("/gameImages/%1a.png").arg(m_task));
    setTaskActivity(true);
}

void GameHandler::imageClicked(int x, int y, int width, int height){
    if(m_taskActive) {
        setTaskActivity(false);
        QImage *img = new QImage(QString(":/gameImages/%1_map.png").arg(m_task), "PNG");

        int newX = img->width()*x/width;
        int newY = img->height()*y/height;

        setImage(QString("/gameImages/%1.png").arg(m_task));
        if( img->pixel(newX,newY) == qRgb(255,255,0)){
            setAnswer("Correct");
        }
        else {
            setAnswer("Wrong");
        }
    }
}


QString GameHandler::getQuestion(){
    return m_question;
}

void GameHandler::setQuestion(QString newValue){
    m_question = newValue;
    emit questionChanged(newValue);
}

QString GameHandler::getAnswer(){
    return m_answer;
}

void GameHandler::setAnswer(QString newValue){
    m_answer = newValue;
    emit answerChanged(newValue);
}

QString GameHandler::getImage(){
    return m_image;
}

void GameHandler::setImage(QString newValue){
    m_image = newValue;
    emit imageChanged(newValue);
}


bool GameHandler::getNextButtonVisibility(){
    return !m_taskActive;
}
void GameHandler::setTaskActivity(bool b){
    m_taskActive = b;
    emit taskActivityChanged();
}

int GameHandler::getMultipler(){
    return m_multiplier;
}

void GameHandler::setMultiplier(int newValue){
    m_multiplier = newValue;
    emit multiplierChanged(newValue);
}

int GameHandler::getPoints(){
    return m_points;
}

void GameHandler::setPoints(int newValue){
    m_points = newValue;
    emit pointsChanged(newValue);
}


