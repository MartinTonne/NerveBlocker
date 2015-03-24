#include "taskannotation.h"

#include <QList>
#include <QDebug>

TaskAnnotation::TaskAnnotation(QObject *parent) :
    QObject(parent),
    yValues((QList<int>())),
    xValues((QList<int>())),
    m_score(0),
    m_answered(false)

{
    yValues<<143<<160<<187<<266<<293;
    xValues<<7<<181<<286<<369<<593;
}

int TaskAnnotation::getScore() const{
    return m_score;
}
QList<int> TaskAnnotation::getXValues() const{
    return xValues;
}

QString TaskAnnotation::getImagePath() const{
    return QString("gameImages/1.png");
}

void TaskAnnotation::answerAnnotationTask(QList<int> answers){
    qDebug() << "Annotation, I got here\n";

    if(answers.size()>0)    {
        qDebug() << "Arguments!\n";
    }

    emit scoreChanged(0);
    emit answeredChanged(false);
}



