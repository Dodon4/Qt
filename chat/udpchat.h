#ifndef UDPCHAT_H
#define UDPCHAT_H
#include<QtWidgets>
#include<QtDebug>
#include<QListWidget>
//#include<QHos
//#include<QTextEdit>
#include<QUdpSocket>
//#include<QLineEdit>

#define HELLO_MARK "#hello#"
#define BYE_MARK "#bye#"

class QLineEdit;
class QTextEdit;
class QUdpSocket;
class udpchat: public QWidget
{
    Q_OBJECT
public:

  explicit udpchat(QString n,QWidget * parent=0);//QString n,
    ~udpchat();
    void startNetworking(int port=34567);
signals:

public slots:
    void sendMessage();
    void showMessage(const QString &n,const QString &message);///////////////////////////////////////////////////////////////////////////////////////////////////////////
    void processPendingDatagrams();
private:
    QString nick;
    QListWidget *activeUsers;
    QTextEdit *messageWindow;
    QLineEdit *message;

    QByteArray encodeMessage(const QString &nick, const QString &message)const;
    QPair<QString,QString> decodeMessage(const QByteArray &ba);

    QUdpSocket *socket;
    quint16 socketPort;
   // QMultiHash<QHostAddress, Connection *> peers;//
};

#endif // UDPCHAT_H
