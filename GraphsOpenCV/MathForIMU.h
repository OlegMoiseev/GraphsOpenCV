#ifndef MATH_FOR_IMU
#define MATH_FOR_IMU

class Quaternion
{
public:
	/**
	 * \brief Real part of quaternion
	 */
	double _w;
	/**
	 * \brief First imagine part of quaternion
	 */
	double _x;
	/**
	* \brief Second imagine part of quaternion
	*/
	double _y;
	/**
	* \brief Third imagine part of quaternion
	*/
	double _z;

	/**
	 * \brief Constructor of the quaternion
	 * \param[in] a Real part of quaternion
	 * \param[in] b First imagine part of quaternion
	 * \param[in] c Second imagine part of quaternion
	 * \param[in] d Third imagine part of quaternion
	 */
	explicit Quaternion(double a = 0., double b = 0., double c = 0., double d = 1.);

};

/**
 * \brief Function of converting quaternion into three angles
 * \param[in] q Quaternion for converting
 * \param[out] roll Roll from quaternion
 * \param[out] pitch Pitch from quaternion
 * \param[out] yaw Yaw from quaternion
 */
void quaternionToEulerianAngle(const Quaternion& q, double& roll, double& pitch, double& yaw);
#endif
