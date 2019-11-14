#ifndef STATICVAR_H
#define STATICVAR_H

#include <QWaitCondition>
#include <QString>

static const int BufferSize = 100;
static int DataSize;
static int RecordedCells = 0;
static int CycleCount = -1;
static char buffer[BufferSize];

static QWaitCondition bufferNotEmpty;
static QWaitCondition bufferNotFull;

static QString fileName;
static QMutex mutex;

#endif // STATICVAR_H
