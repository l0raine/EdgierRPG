#ifndef QUEST_SCRIPT_HPP
#define QUEST_SCRIPT_HPP

#include <memory>

#include "Script.hpp"

/*
Quest scripts will be setup as follows:

A Start() function for initializing anything the quest needs
A Load() function for receiving data from a saved quest file.
A Save() function for passing data to be saved and loaded later.

An Objectives table actually contains more tables
The order of the inner tables in the Objectives table is the order of
objectives to be completed by the player.
For example, the 2nd objective in the table will not be visible or available
to the player until the first 1st is completed.
If order is not desired, then work them all into a single objective (for now at least).

Each inner table contains:
	A string describing the objective (to the player)
	A 'task' function forming the logic checking the status of the objective.
		Will return 2, 1, or 0.
		2: Success
		1: Still in-progress
		0: Fail
	Success/Fail messages
	Another function, that will be run once the objective is
		complete (on success OR fail). Has a bool argument indicating
		success (true) or failure (false).

Having an Objective class in C++ might simplify this.

Here's an example script that gives the player some experience when
he arrives at a predetermind random position:

local goal = {x = -1, y = -1}
local player = nil

function Start()
	math.randomseed(os.time())

	--call random a few times to improve results
	math.random(); math.random(); math.random()

	--generate random coordinate
	goal.x = math.random(0, 100)	--should be widget/height of the map of course
	goal.y = math.random(0, 100)

	--C++ function call
	player = getPlayer()
end

function Load(...)
	--if the argument list is not empty...
	if select('#', ...) > 0 then
		goal.x, goal.y = ...
	end
end

function Save()
	return goal.x, goal.y
end

Objectives =
{
	{
		 description = "Reach the position "..goal.x..", "..goal.y.."!",
		 start = function()
			--highlight position on minimap?
		 end,
		 task = function()
			if player.position.x == goal.x and player.position.y == goal.y then
				return SUCCESS
			elseif player.position.x < 0 or player.position.x > 100 or player.position.y < 0 or player.position.y > 100 then
				--left the map
				return FAILURE
			else
				return IN_PROGRESS
			end
		 end,
		 success = "Congrats! Here is 50 gold.",
		 failure = "How the hell did you fail this?",
		 complete = function(success)
			--example of possible usage
			if success then
				player.inventory.wallet.add(50)
			else
				player.sadness = player.sadness + 100
			end
		 end
	}
	--if there were more objectives, then there would be more inner tables like the one above
}
*/

class QuestScript : public Script
{
public:
    QuestScript();
    ~QuestScript();

    // returns true if script loaded alright and is safe to update, false otherwise
    bool initialize(const std::string& file);

    // returns true if this quest should continue to be updated (ie, not complete)
    // false if it's done (success or failure)
    bool update();

    // need to work out how this will work
    bool save();

    const std::string& getCurrentDescription();
    const std::string& getCurrentSuccess();
    const std::string& getCurrentFailure();

    // TODO: Need a good way to report the status of the current objective (success, failure, in progress)

private:
    void updateObjective();

    bool scriptLoaded;

    std::size_t currentObjectiveIdx;
    std::size_t totalObjectives;

    std::unique_ptr<lna::Selection> currentTask;
    std::unique_ptr<lna::Selection> currentComplete;

    std::string description;
    std::string success;
    std::string failure;
};

#endif
