#ifndef XFXHAPI_H
#define XFXHAPI_H

#include <QObject>

#include "llmbase.h"

class XfxhApi : public LLMBase
{
    Q_OBJECT

public:
    explicit XfxhApi(QObject *parent = nullptr);
public:
    void start(const QString& str)override;
private:
    void init();
    void initConnect();
signals:

public slots:
};

#endif // XFXHAPI_H
