#include <stdio.h>
#include "GameActor.hpp"
#include <nima/Animation/ActorAnimation.hpp>
#include <nima/Exceptions/OverflowException.hpp>
#include <nima/Exceptions/UnsupportedVersionException.hpp>
#include <nima/Animation/Interpolators/CubicSolver.hpp>
//#include "Graphics/Bitmap/Bitmap.hpp"
//#include "Graphics/OpenGL/GLRenderer2D.hpp"
#include "ArcherController.hpp"
#include <cmath>

// The input is handled globally in this example for the sake of simplicity and clarity.
nima::Vec2D screenMouse;


int main(int argc, char** argv)
{

	int initialWindowWidth = 640;
	int initialWindowHeight = 480;

	
	nima::Vec2D m_ViewCenter(0.0f, 0.0f);
	float m_CameraScale = 0.5f;
	nima::Mat2D viewTransform;
	nima::Mat2D inverseViewTransform;



	// Init renderer.
	//nima::Renderer2D* renderer = new nima::GLRenderer2D();
	void* renderer = 0;


	nima::GameActor* actor = new nima::GameActor();

	try
	{
		//actor->load("Assets/Archer Work.nima");
		actor->load("Assets/Jelly Bow.nima");
	}
	catch (nima::OverflowException ex)
	{
		printf("Bad data, got an overflow.\n");
	}
	catch (nima::UnsupportedVersionException ex)
	{
		printf("Unsupported version. %d %d\n", ex.versionFound(), ex.versionRequired());
	}

	actor->initializeGraphics(renderer);

	nima::GameActorInstance* actorInstance = actor->instance<nima::GameActorInstance>();
	actorInstance->initializeGraphics(renderer);

	nima::ActorAnimation* animation = actorInstance->animation("Untitled");
	float animationTime = 0.0f;
	//characterController = actorInstance->addController<ArcherController>();

	int width = 0, height = 0;
	int lastScreenWidth = width, lastScreenHeight = height;

	
	printf("\n Start loop");
	
	//while (true)
	{
		
		/*
		glfwGetFramebufferSize(window, &width, &height);
		if (width != lastScreenWidth || height != lastScreenHeight)
		{
			lastScreenWidth = width;
			lastScreenHeight = height;
			// resized.
			renderer->setViewportSize(width, height);

			viewTransform[0] = m_CameraScale;
			viewTransform[3] = m_CameraScale;
			viewTransform[4] = (-m_ViewCenter[0] * m_CameraScale + width/2.0f);
			viewTransform[5] = (-m_ViewCenter[1] * m_CameraScale + height/2.0f);
			renderer->setView(viewTransform);

			nima::Mat2D::invert(inverseViewTransform, viewTransform);
		}*/
		
		
		nima::Vec2D worldMouse(screenMouse[0], lastScreenHeight - screenMouse[1]);
		nima::Vec2D::transform(worldMouse, worldMouse, inverseViewTransform);

		//double time = glfwGetTime();
		double lastTime = 0;
		double time = 0;
		float elapsed = (float)(time - lastTime);
		lastTime = time;

		if(animation != nullptr)
		{
			animationTime = std::fmod(animationTime + elapsed, animation->duration());
			animation->apply(animationTime, actorInstance, 1.0f);
		}
		/*
		if(characterController != nullptr)
		{
			characterController->setAimTarget(worldMouse);
		}*/
		
		actorInstance->advance(elapsed);

		//renderer->clear();
		actorInstance->render(renderer);

		//glfwSwapBuffers(window);
		//glfwPollEvents();
	}

	printf("\n ******** END ************ \n");
	// Cleanup.
	//delete actorInstance;
	//delete actor;
	//delete renderer;

	return 0;
}
