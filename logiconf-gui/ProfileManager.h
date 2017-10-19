#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include <QObject>

class ProfileManager : public QObject
{
    Q_OBJECT
public:
    explicit ProfileManager(QObject *parent = 0);

signals:

public slots:
};

#endif // PROFILEMANAGER_H