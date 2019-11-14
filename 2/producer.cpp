#include "producer.h"
#include "staticvar.h"
#include <QFile>



/*void Producer::run()
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);

    for (int i=0; i<DataSize; ++i)
    {
        mutex.lock();
        if (RecordedCells == BufferSize)
            bufferNotFull.wait(&mutex);
        mutex.unlock();

        QObject().thread()->usleep(1000*25*1);
        file.read(&(buffer[i % 100]),1);
        emit ProducerUpdate(QString(buffer));
        mutex.lock();
        ++RecordedCells;
        bufferNotEmpty.wakeAll();
        mutex.unlock();
    }

    file.close();
}
*/
