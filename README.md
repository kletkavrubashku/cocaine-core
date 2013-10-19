What the hell is it? [![Build Status](https://travis-ci.org/cocaine/cocaine-core.png?branch=master)](https://travis-ci.org/cocaine/cocaine-core)
====================

> If you wanna hang out you've got to take her out; cocaine.<br>
> If you wanna get down, down on the ground; cocaine.<br>
> She don't lie, she don't lie, she don't lie; cocaine.<br>

-- [J. J. Cale](http://en.wikipedia.org/wiki/JJ_Cale), cover version by [Eric Clapton](https://www.youtube.com/watch?v=Q3L4spg8vyo)

__Your personal app engine.__ Technically speaking, it's an open-source cloud platform enabling you to build your own PaaS clouds using simple yet effective dynamic components.

Notable features:

* You are not restricted by a language or a framework. Similar to Heroku model, Cocaine simply spawns whatever you tell it to spawn. The only requirement is that these newly spawned apps must connect to their app controller for request load balancing. But we plan to get rid of this last requirement as well.
* Your apps are driven by events, which is fancy. There are two sources of events for every app, and we got lots of predefined plugins providing those sources, so unless you need to handle clients via a PS/2 port, you're good.
  * First, there are services: this concept is similar to Google App Engine's services. Simply speaking, services are other apps running in the same cloud. These apps can be anything ranging from a distributed storage access service or a publish-subscribe notification service to specially-crafted service for your own personal needs.
  * Second, there are event drivers: these are simple statically configurable objects attached to your app generating events from some predefined source, for example a recurring timer or a watched file on the filesystem.
* We got dynamic self-managing worker pools for each app with a rich but simple configuration and resource usage control to scale with the app needs. Yeah, it's scales automatically, you don't need to think about it. As of now, we got support for CGroups and LXC containerization via [Docker](http://docker.io).
* Even more, it scales automatically across your server cluser via automatic node discovery and smart peer-to-peer balancing. You can use a simple adhoc round-robin balancing for simple setups or a hardcore IPVS-based realtime balancer.
* If your startup idea is about processing terabytes of pirated video, we got data streaming and pipelining for you as well, enjoy.

At the moment, Cocaine Core supports the following languages and specifications:

* C++
* Python
* Node.js
* Java
* Go
* [In development] Racket

We have the following services:

* Logging
* Node-local file storage
* MongoDB storage
* [Elliptics](https://github.com/reverbrain/elliptics) storage
* Node-local in-memory cache
* Distributed in-memory cache
* URL Fetch
* Jabber
* [In development] Notifications
* [In development] Distributed time service

And the following event drivers built-in:

* Simple timer
* Filesystem monitor
* ZeroMQ

A motivating example
====================

Here's some extremely useful Cocaine app written in Python.

```python
#!/usr/bin/env python

from cocaine.services import Service
from cocaine.worker import Worker

storage = Service("storage")

def process(value):
    return len(value)

def handle(request, response):
    key = yield request.read()
    value = yield storage.read("collection", key)

    response.write(process(value))
    response.close()

Worker().run({
    'calculate_length': handle
})
```

Okay, I want to try it!
=======================

Hey kids, don't try cocaine! For serious web developers only.

Check out [our wiki](https://github.com/cocaine/cocaine-core/wiki) for installation instructions, reference manuals and cookies! We also got a bit [outdated docs](https://github.com/cocaine/cocaine-docs-en/wiki) for v0.9, but worry not, up-to-date documentation is on its way!
