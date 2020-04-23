#ifndef S_KINEMATICS_H
#define S_KINEMATICS_H

namespace s_Kinematics
{
	/*
	 * updateKinematics
	 *
	 * Function performs kinematics on the passed entity to
	 * update entity's position and velocity base on it's
	 * current position, velocity, and acceleration.
	 *
	 * @Param: Entity which the kinematic operation will be performed on.
	 */
	void updateKinematics(const unsigned int& ID);
}

#endif //S_KINEMATICS_H
