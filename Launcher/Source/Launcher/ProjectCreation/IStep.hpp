#pragma once

namespace Launcher
{
namespace ProjectCreation
{
class IStep
{
public:
	virtual bool hasError() = 0;
	virtual bool moveBack() = 0;
	virtual bool moveNext() = 0;
};
}
}
