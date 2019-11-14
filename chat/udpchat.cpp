#include "udpchat.h"
#include<QLayout>
#include<QTextEdit>
#include<QLabel>
#include <QTime>
#include<QListWidget>

udpchat::udpchat(QString n,QWidget * parent):QWidget(parent)//
{
    socket = 0;
    nick = n;
    QHBoxLayout *l = new QHBoxLayout(this);
    QVBoxLayout *messageLayout=new QVBoxLayout;
    qDebug() << "NAME : '" << n << "'" << endl;
    activeUsers = new QListWidget(this);
    activeUsers->setMaximumWidth(150);

    messageWindow=new QTextEdit;
    messageWindow->setReadOnly(true);
    message=new QLineEdit;
    messageLayout->addWidget(messageWindow);
    messageLayout->addWidget(message);

    l->addWidget(activeUsers);
    l->addLayout(messageLayout);

    connect(message,SIGNAL(returnPressed()),this,SLOT(sendMessage()));



}
udpchat::~udpchat()
{
    qDebug()<<socket;
    QByteArray data=encodeMessage(nick,BYE_MARK);
    socket->writeDatagram(data,QHostAddress::Broadcast,socketPort);
}

void udpchat::startNetworking(int port)
{

    socket = new QUdpSocket;
    qDebug() << "PORT: '" << port << "'" << endl;
    socketPort =port;
    qDebug() << "bind port" << socketPort << socket-> bind(socketPort,QAbstractSocket::ShareAddress
                                                           | QAbstractSocket::ReuseAddressHint);
    connect(socket,SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));
    QByteArray data=encodeMessage(nick,HELLO_MARK);
    quint16 bytes=socket->writeDatagram(data,QHostAddress::Broadcast,socketPort);
    socket->writeDatagram(data, QHostAddress::Broadcast,socketPort);


    qDebug()<<"start"<<nick<<HELLO_MARK;

}
void udpchat::sendMessage(){
    QByteArray data=encodeMessage(nick,message->text());
    socket->writeDatagram(data,QHostAddress::Broadcast,socketPort);

}

void udpchat::showMessage(const QString &n, const QString &message)
{
QTime time=QTime::currentTime();
QString line=QString("<font color=\"%4\">[%1]<b>%2</b></font>:%3").arg(time.toString()).arg(n).arg(message).arg(n==nick ?"red":"blue");
messageWindow->append(line);
}

void udpchat::processPendingDatagrams()
{
    QByteArray buffer;
    while(socket->hasPendingDatagrams()){
        buffer.resize((socket->pendingDatagramSize()));
        socket->readDatagram(buffer.data(),buffer.size());

    QPair<QString,QString> pair=decodeMessage(buffer);

    if(pair.second==HELLO_MARK){
        if(pair.first !=nick){
            QList<QListWidgetItem*> au=activeUsers->findItems(pair.first,Qt::MatchExactly);
            if(au.empty()){
                activeUsers->addItem(pair.first);
                QByteArray data=encodeMessage(nick,HELLO_MARK);
                socket->writeDatagram(data,QHostAddress::Broadcast,socketPort);
            }
        }
        else
            qDebug()<<"ignore user";
    }
    else if(pair.second==BYE_MARK){
        for(int r=0; r<activeUsers->count(); r++){
            if(activeUsers->item(r)->text()==pair.first){
                activeUsers->takeItem(r);
                break;
            }
        }

    }
    else showMessage(pair.first,pair.second);
    }
}

QByteArray udpchat::encodeMessage(const QString &nick, const QString &message) const
{
    QByteArray ba;
    QDataStream stream(&ba,QIODevice::WriteOnly);
    stream<<nick<<message;
    return ba;


}

QPair<QString, QString> udpchat::decodeMessage(const QByteArray &ba)
{
    QDataStream stream(ba);
    QString nick,msg;
    stream>>nick>>msg;
    return qMakePair(nick,msg);

}

