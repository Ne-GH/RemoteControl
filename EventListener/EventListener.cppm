/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/10/26 22:27
*******************************************************************************/
module;
#include <mutex>
#include <thread>
#include <map>
#include <string>
#include <condition_variable>

#include <iostream>
#include <X11/Xlib.h>
#include <X11/keysym.h>
export module EventListener;

auto RegisterKey(Display *display,Window root) {
    std::map<std::string,int> keys;
#define TOCODE(key) keys[#key] = XKeysymToKeycode(display,XK_##key)
    TOCODE(a);
    TOCODE(b);
    TOCODE(c);
    TOCODE(d);
    TOCODE(e);
    TOCODE(f);
    TOCODE(g);
    TOCODE(h);
    TOCODE(i);
    TOCODE(j);
    TOCODE(k);
    TOCODE(l);
    TOCODE(m);
    TOCODE(n);
    TOCODE(o);
    TOCODE(p);
    TOCODE(q);
    TOCODE(r);
    TOCODE(s);
    TOCODE(t);
    TOCODE(u);
    TOCODE(v);
    TOCODE(w);
    TOCODE(x);
    TOCODE(y);
    TOCODE(z);

    TOCODE(A);
    TOCODE(B);
    TOCODE(C);
    TOCODE(D);
    TOCODE(E);
    TOCODE(F);
    TOCODE(G);
    TOCODE(H);
    TOCODE(I);
    TOCODE(J);
    TOCODE(K);
    TOCODE(L);
    TOCODE(M);
    TOCODE(N);
    TOCODE(O);
    TOCODE(P);
    TOCODE(Q);
    TOCODE(R);
    TOCODE(S);
    TOCODE(T);
    TOCODE(U);
    TOCODE(V);
    TOCODE(W);
    TOCODE(X);
    TOCODE(Y);
    TOCODE(Z);
    for (const auto& p : keys) {
        XGrabKey(display, p.second, 0, root, True, GrabModeAsync, GrabModeAsync);
    }

    return keys;
#undef TOCODE
}

void DisRegisterKey(Display *display,Window root,std::map<std::string,int> &keys) {
    for (const auto &p : keys) {
        XUngrabKey(display,p.second,0,root);
    }
}

export class KeyEventListener {
    unsigned long lastReleaseTime = 0;
    Window root;
    XEvent event;
    Display *display;
    std::map<std::string,int> keys;

    bool listen = false;
    std::mutex mutex;
    std::condition_variable cv;
    std::thread thread;

public:
    KeyEventListener() {
        thread = std::thread(&KeyEventListener::Listen,this);
        thread.detach();
    }
    void Listen() {
        {
            std::lock_guard<std::mutex> lock(mutex);
            listen = true;
        }

        display = XOpenDisplay(0);

        root = DefaultRootWindow(display);

        int F4 = XKeysymToKeycode(display, XStringToKeysym("F4"));
        std::cout << F4 << std::endl;
        int F6 = XKeysymToKeycode(display, XStringToKeysym("F6"));

        //Register the keys
        XGrabKey(display, F4, 0, root, True, GrabModeAsync, GrabModeAsync);
        XGrabKey(display, F6, 0, root, True, GrabModeAsync, GrabModeAsync);

        keys = RegisterKey(display,root);

        while (listen) {

            XNextEvent(display,&event);
            if (event.type == KeyPress && event.xkey.time != lastReleaseTime) {
                if (event.xkey.keycode == F4)
                    return;
                if (event.xkey.keycode == keys["a"])
                    std::cout << "a" << std::endl;

                else if (event.xkey.keycode == keys["b"])
                    std::cout << "b" << std::endl;
                else if (event.xkey.keycode == keys["c"])
                    std::cout << "c" << std::endl;
                else if (event.xkey.keycode == F6)
                    std::cout << "F6" << std::endl;
                //do something...
            }
            else if (event.type == KeyRelease) {
                lastReleaseTime = event.xkey.time;
            }
        }
    }

    void DisListen() {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock,[&]{return listen;});
        listen = false;
        DisRegisterKey(display,root,keys);
    }

};