#ifndef SFMLTEST_H
#define SFMLTEST_H

#include <SFML/Window.hpp>
#include <iostream>
#include <QThread>

class sfmltest : public QThread
{
public:
    sfmltest();

protected:
    void run();
};

#endif // SFMLTEST_H
