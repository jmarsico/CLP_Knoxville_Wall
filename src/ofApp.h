// =============================================================================
//
// Copyright (c) 2014-2015 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#pragma once


#include "ofMain.h"
#include "ofxJSONRPC.h"


class ofApp: public ofBaseApp
{
public:
    void setup();
    void draw();
    void exit();

    // Registered methods.
    void getText(ofx::JSONRPC::MethodArgs& args);
    void setText(ofx::JSONRPC::MethodArgs& args);
    
    void getSlider(ofx::JSONRPC::MethodArgs& args);

    // Register a no-argument notification method.
    void ping();

    // Register a no-argument notification method.
    void pong();
    
    

    /// \todo is ofSoundPlayer thread-safe?
    ofSoundPlayer pingPlayer;
    ofSoundPlayer pongPlayer;

    /// \brief The server that handles the JSONRPC requests.
    ofx::HTTP::JSONRPCServer server;
    
    ofx::HTTP::SimpleFileServer studentserver;

    /// \brief Get a snippet of random text in a thread-safe way.
    /// \returns The snippet of random text.
    std::string getRandomText() const;

    /// \brief Get the user text in a thread-safe way.
    /// \returns The user text.
    std::string getUserText() const;

    /// \brief Set the user text in a thread-safe way.
    /// \param text the user text to set.
    void setUserText(const std::string& text);

private:
    // A custom logging channel to mirror all log messages to the web clients.
    // WebSocketLoggerChannel::SharedPtr loggerChannel;

    // This piece of text might be modified by multiple client threads.
    // Thus we must use a mutex to protect it during multi-threaded access.
    std::string ipsum;

    // This piece of text might be modified by multiple client threads.
    // Thus we must use a mutex to protect it during multi-threaded access.
    std::string userText;

    // We use a mutex to protect any variables that can be
    // modified by multiple clients.  In our case, userText must be protected.
    // We mark the mutex as mutable so that it can be used in const functions.
    mutable std::mutex mutex;

};
