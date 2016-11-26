﻿#ifndef SABA_VIEWER_VIEWER_H_
#define SABA_VIEWER_VIEWER_H_

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "ViewerContext.h"
#include "Grid.h"
#include "ModelDrawer.h"

#include "../GL/GLObject.h"
#include "../GL/Model/OBJ/GLOBJModelDrawContext.h"

#include <memory>

namespace saba
{
	class ImGUILogSink;

	class Viewer
	{
	public:
		Viewer();
		~Viewer();

		bool Initialize();
		void Uninitislize();

		int Run();

	private:
		struct Mouse
		{
			Mouse();
			void Initialize(GLFWwindow* window);
			void Update(GLFWwindow* window);
			void SetScroll(double x, double y);

			double	m_prevX;
			double	m_prevY;
			double	m_dx;
			double	m_dy;

			double	m_saveScrollX;
			double	m_saveScrollY;
			double	m_scrollX;
			double	m_scrollY;
		};

		enum class CameraMode
		{
			None,
			Orbit,
			Dolly,
			Pan,
		};

	private:
		void Draw();
		void DrawLogUI();

		bool LoadOBJFile(const std::string& filename);

		static void OnMouseButtonStub(GLFWwindow* window, int button, int action, int mods);
		void OnMouseButton(int button, int action, int mods);

		static void OnScrollStub(GLFWwindow* window, double offsetx, double offsety);
		void OnScroll(double offsetx, double offsety);

		static void OnKeyStub(GLFWwindow* window, int key, int scancode, int action, int mods);
		void OnKey(int key, int scancode, int action, int mods);

		static void OnCharStub(GLFWwindow* window, unsigned int codepoint);
		void OnChar(unsigned int codepoint);

		static void OnDropStub(GLFWwindow* window, int count, const char** paths);
		void OnDrop(int count, const char** paths);

	private:
		ViewerContext	m_context;
		std::unique_ptr<GLOBJModelDrawContext>	m_objModelDrawContext;

		std::unique_ptr<ModelDrawer>	m_modelDrawer;

		bool		m_glfwInitialized;
		GLFWwindow*	m_window;

		GLProgramObject		m_bgProg;
		GLVertexArrayObject	m_bgVAO;
		GLint			m_uColor1;
		GLint			m_uColor2;

		Mouse		m_mouse;
		CameraMode	m_cameraMode;
		Grid		m_grid;

		// LogWindow
		std::shared_ptr<ImGUILogSink>	m_imguiLogSink;
		bool							m_enableLogUI;
	};
}

#endif // !SABA_VIEWER_VIEWER_H_
