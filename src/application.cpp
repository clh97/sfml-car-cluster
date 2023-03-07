#include "platform.cpp"

class Application
{
public:
    Application(std::unique_ptr<PlatformAdapter> adapter, const char *title, int width, int height)
        : m_adapter(std::move(adapter))
    {
        m_window = m_adapter->CreateWindow(title, width, height);
        m_adapter->SetCurrentContext(m_window);

        SDL_GL_CreateContext(m_window);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        glViewport(0, 0, width, height);
    }

    ~Application()
    {
        m_adapter->DestroyWindow(m_window);
    }

    void Run()
    {
        bool quit = false;
        while (!quit)
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    quit = true;
                }
            }

            Update();
            Render();
            m_adapter->SwapBuffers(m_window);
        }
    }

private:
    void Update()
    {
        // no-op
    }

    void Render()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(0.0f, 0.5f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(0.5f, -0.5f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(-0.5f, -0.5f);
        glEnd();

        glFlush();
    }

    std::unique_ptr<PlatformAdapter> m_adapter;
    SDL_Window *m_window;
};
