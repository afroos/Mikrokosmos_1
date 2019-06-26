#include <iostream>
#include <iomanip>
#include <Mikrokosmos.hpp>

using namespace Mikrokosmos;

int main() 
{
	World world{};
	/*world.setGravity(LinearAcceleration2{ 0.0_mps2, -9.81_mps2 }); */

	auto groundMaterial = std::make_shared<Material>();
	groundMaterial->setDensity(5.0_kgpm2);
	groundMaterial->setRestitution(0.6);
	groundMaterial->setStaticFriction(2.0);
	groundMaterial->setDynamicFriction(1.0);

	Length2 groundHalfextents{ 0.5_m, 1.0_m };
	auto groundShape = make_shared<Box>(groundHalfextents);



	/*
	Collider groundCollider{ groundShape, groundMaterial };

	auto groundBody = make_shared<Body>();
	groundBody->add{ groundCollider };
	groundBody->setPose(Transform{ Length2{0.0_m, 1.0_m}, Angle{0_deg} });
	world.add(groundBody);

	auto ballMaterial = make_shared<Material>();
	ballMaterial->setDensity(1.0_kgpm2);
	ballMaterial->setRestitution(0.7);
	ballMaterial->setStaticFriction(3.0);
	ballMaterial->setDynamicFriction(2.0);

	Length2 radius{ 0.25_m };
	auto ballShape = make_shared<Circle>(radius);

	Collider ballCollider{ ballShape, ballMaterial };

	auto ballBody = make_shared<Body>();
	ballBody->add{ ballCollider };
	ballBody->setPose(Transform{ Length2{0.0_m, 15.0_m}, Angle{0_deg} });
	world.add(ballBody);
	*/
	Time timeStep = 1.0_s / 60.0;
	for (size_t i = 0; i < 60; ++i)
	{
		std::cout << setprecision(2) << fixed
			<< "Time: " << setw(5) << i * timeStep << ", "
			<< "position: " << setw(5) << ballBody.position() << ", "
			<< "velocity: " << setw(5) << ballBody.linearVelocity() << std::endl;
		world.step(timeStep);
	}
}