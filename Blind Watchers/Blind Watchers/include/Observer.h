#pragma once

#include <vector>
#include <iostream>

// abstract class for derived classes to use
template <typename Observer> class ObserverSubjectTemplate
{
public:
    template <typename T> void AddObserver(T t_newObserver)
    {
        m_observers.push_back(t_newObserver);
    }
    template <typename arg>void notifyAll(arg& t_item)
    {
        for (auto i : m_observers)
        {
            i->listen(t_item);
        }
    }
private:
    std::vector< std::shared_ptr<Observer> > m_observers;
};

class ObserverTemplate
{
public:
    template <typename T> void listen(T t_arg) = 0;
};
