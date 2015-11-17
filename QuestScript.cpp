#include "QuestScript.hpp"
#include "make_unique.h"

namespace
{
	static const std::size_t SUCCESS = 2;
	static const std::size_t IN_PROGRESS = 1;
	static const std::size_t FAILURE = 0;
}

QuestScript::QuestScript()
:	currentObjectiveIdx(1),	// Lua tables are 1-indexed, not 0-indexed
	totalObjectives(0)
{}

QuestScript::~QuestScript()
{}

bool QuestScript::initialize(const std::string& file)
{
	if(openFile(file))
	{
		// make status values visible to Lua
		luaState["SUCCESS"] = SUCCESS;
		luaState["IN_PROGRESS"] = IN_PROGRESS;
		luaState["FAILURE"] = FAILURE;

		luaState["Start"]();

		// pass any saved variables to this call
		luaState["Load"]();

		// run Lua code to query number of objectives
		luaState("numObjs = #Objectives");
		totalObjectives = luaState["numObjs"];

		// quest save file should contain the current objective index
//		currentObjectiveIdx = blahBlahBlah

		updateObjective();

		return true;
	}
	else
	{
		return false;
	}
}

// may have to play with the objective failure logic to get it to exactly what we want
bool QuestScript::update()
{
	std::size_t status = (*currentTask)();

	if(status != IN_PROGRESS)
	{
		bool success = status == SUCCESS;

		(*currentComplete)(success);

		if(success)
		{
			++currentObjectiveIdx;

			if(currentObjectiveIdx <= totalObjectives)
			{
				updateObjective();
				return true;
			}
		}

		return false;
	}

	return true;
}

bool QuestScript::save()
{
	return false;
}

const std::string& QuestScript::getCurrentDescription()
{
	return description;
}

const std::string& QuestScript::getCurrentSuccess()
{
	return success;
}

const std::string& QuestScript::getCurrentFailure()
{
	return failure;
}

void QuestScript::updateObjective()
{
	// cache functions and strings so we don't have to index to them every update
	auto objective = luaState["Objectives"][currentObjectiveIdx];
	currentTask = std::make_unique<lna::Selection>(objective["task"]);
	currentComplete = std::make_unique<lna::Selection>(objective["complete"]);
	description = objective["description"].operator std::string();
	success = objective["success"].operator std::string();
	failure = objective["failure"].operator std::string();

	// initialize objective
	objective["start"]();
}
