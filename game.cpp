#include "game.h"
#include "task.h"
#include "constants.h"

#include <QDebug>


Game::Game(Mode::Type mode, QObject *parent):
    QObject(parent),
    m_currentTask(nullptr),
    m_currentVideoTask(nullptr),
    m_currentAnnotationTask(nullptr),
    m_points(0),
    m_multiplier(1),
    m_tasksAnswered(0),
    m_tasksAnsweredCorrectly(0),
    m_maxPoints(0),
    m_mode(mode)
{
    if(mode == Mode::VIDEO)
        newVideoTask();
    if(mode == Mode::DRAG)
        newAnnotationTask();
    else
        newTask();
}

Task *Game::getCurrentTask()
{
    return m_currentTask;
}
TaskVideo *Game::getCurrentVideoTask()
{
    return m_currentVideoTask;
}
TaskAnnotation* Game::getCurrentAnnotationTask(){
    return m_currentAnnotationTask;

}



bool Game::isFinished() const
{
    return m_tasksAnswered >= MAX_TASKS_PER_GAME;
}

Mode::Type Game::getMode()
{
    return m_mode;
}

void Game::newTask()
{

    if(m_currentTask!=nullptr)
        m_currentTask->deleteLater();
    m_currentTask = Task::createRandomTask(this);
    m_currentTask->connect(m_currentTask, &Task::answeredChanged,
                           this, &Game::onTaskAnswered);

    emit currentTaskChanged(m_currentTask);
}
void Game::newVideoTask()
{

    if(m_currentVideoTask!=nullptr)
        m_currentVideoTask->deleteLater();
    m_currentVideoTask = new TaskVideo(this);
    m_currentVideoTask->connect(m_currentVideoTask, &TaskVideo::answeredChanged,
                           this, &Game::onVideoTaskAnswered);

    Game::setMaxPoints();

    emit currentVideoTaskChanged(m_currentVideoTask);
}
void Game::newAnnotationTask(){
    if(m_currentAnnotationTask!=nullptr)
        m_currentAnnotationTask->deleteLater();
    m_currentAnnotationTask = new TaskAnnotation(this);
    m_currentAnnotationTask->connect(m_currentAnnotationTask, &TaskAnnotation::answeredChanged,
                           this, &Game::onAnnotationTaskAnswered);
    Game::setMaxPoints();

    emit currentAnnotationTaskChanged(m_currentAnnotationTask);
}


void Game::onTaskAnswered()
{
    bool oldFinished = isFinished();
    m_tasksAnswered++;
    if(m_currentTask->isCorrect())
        m_tasksAnsweredCorrectly++;
    emit tasksAnsweredChanged(m_tasksAnswered);


    // Adding points
    if (getMode()==Mode::DRAG) {
        setPoints(getPoints() + m_currentTask->getScore());
    }
    else {
        if(m_currentTask->isCorrect()){
            int receivedPoints = 50 * getMultiplier();
            setPoints(getPoints() + receivedPoints);
            setMultiplier(getMultiplier()+1);
        } else {
            setMultiplier(1);
        }
    }

    bool newFinished = isFinished();
    if(oldFinished != newFinished)emit finishedChanged(newFinished);
}

void Game::onVideoTaskAnswered(){
     setPoints(m_currentVideoTask->getScore());
}
void Game::onAnnotationTaskAnswered(){
     setPoints(m_currentAnnotationTask->getScore());
}

int Game::getMultiplier() const {
    return m_multiplier;
}

void Game::setMultiplier(int newValue){
    m_multiplier = newValue;
    emit multiplierChanged(newValue);
}

int Game::getPoints() const {
    return m_points;
}

void Game::setPoints(int newValue){
    m_points = newValue;
    emit pointsChanged(newValue);
}
void Game::setMaxPoints(){
    if(m_mode == Mode::DRAG){
        m_maxPoints = m_currentAnnotationTask->getMaxScore();
        emit maxPointsChanged(m_maxPoints);
    }
    else if(m_mode == Mode::VIDEO){
        m_maxPoints = m_currentVideoTask->getMaxScore();
        emit maxPointsChanged(m_maxPoints);
    }
}
