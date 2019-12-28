


#ifndef AUTONOMOUS_COMMAND_H
#define AUTONOMOUS_COMMAND_H


#include "frc/commands/Subsystem.h"
#include "Robot.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class AutonomousCommand: public frc::Command {
public:
	AutonomousCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
};

#endif
