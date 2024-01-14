#pragma once


namespace Real
{
class GLObject
{
public:
    virtual ~GLObject() {};
    virtual void bind() = 0;
    virtual void unbind() = 0;
};
}