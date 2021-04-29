#include <assert.h>
#include <list>

//#define METHOD_HANDLER( Object, Method ) createMethodEventHandler( Object, &Method )
#define EVENT_HANDLER( Method ) createEventHandler( *this, Method )

template<class ...TParams>
class AbstractEventHandler
{
protected:
    AbstractEventHandler() {}

public:
    virtual int call(TParams... params) = 0;
};

template<class ...TParams>
class TEvent
{
private:
    using TEventHandler = AbstractEventHandler<TParams...>;
    std::list<TEventHandler*> m_handlers;

public:
    TEvent() : m_handlers() {}

    ~TEvent()
    {
        for (TEventHandler* oneHandler : m_handlers)
        {
            //delete oneHandler;
        }

        m_handlers.clear();
    }

    int operator()(TParams... params)
    {
        for (TEventHandler* oneHandler : m_handlers)
        {
            return oneHandler->call(params...);
        }

        return 0;
    }

    void operator+=(TEventHandler& eventHandler)
    {
        m_handlers.push_back(&eventHandler);
    }
};

template<class TObject, class ...TParams>
class MethodEventHandler : public AbstractEventHandler<TParams...>
{
private:
    using TMethod = int(TObject::*)(TParams...);

public:
    MethodEventHandler(TObject& object, TMethod method) : AbstractEventHandler<TParams...>(),
        m_object(object), m_method(method)
    {
        assert(m_method != nullptr);
    }

    virtual int call(TParams... params) override final
    {
        return (m_object.*m_method)(params...);
    }

private:
    TObject& m_object;
    TMethod m_method;
};

template<class TObject, class ...TParams>
AbstractEventHandler<TParams...>& createEventHandler(TObject* object, int(TObject::* method)(TParams...))
{
    return *new MethodEventHandler<TObject, TParams...>(*object, method);
}