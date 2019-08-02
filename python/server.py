#!/usr/bin/env python3
# coding: utf-8
'''基于aiohttp的基本的服务器程序'''

import time
import asyncio
import sys
import json
import os
import functools
import logging
from logging.handlers import RotatingFileHandler
import aiohttp
from aiohttp import web
import signal

json_dumps = functools.partial(json.dumps, separators=(',', ':'))
json_loads = json.loads

try:
    import uvloop
    asyncio.set_event_loop_policy(uvloop.EventLoopPolicy())
except ImportError:
    pass

__all__ = []

g_version_info = (0, 1, 0)
g_version = '.'.join(map(str, g_version_info))

class MyLogger:
    def __init__(self, logfname, maxBytes=1024*1024, backupCount=100):
        self.logfname = logfname

        self.logger = logging.getLogger(logfname)
        self.logger.setLevel(logging.INFO)

        handle = RotatingFileHandler(os.path.abspath(logfname),
                                     maxBytes=maxBytes,
                                     backupCount=backupCount)
        formatter = logging.Formatter("[%(asctime)s] %(levelname)s: %(message)s")
        handle.setFormatter(formatter)
        self.logger.addHandler(handle)

    def log(self, *args, sep=' '):
        msg = sep.join(map(str, args))
        self.logger.info(msg)

g_logfname = os.path.splitext(os.path.basename(sys.argv[0]))[0] + '.log'
g_logger = MyLogger(g_logfname)

def log(*args, sep=' '):
    global g_logger
    print(*args, sep=sep)
    g_logger.log(*args, sep=sep)

def pjson(j):
    print(json.dumps(j, indent=4, ensure_ascii=False, sort_keys=True))

get_strtime = lambda: time.strftime('%Y-%m-%d %H:%M:%S %z')

def json_resp(func):
    @functools.wraps(func)
    async def wrapper(*args, **kwargs):
        result = await func(*args, **kwargs)
        return web.Response(text=json_dumps(result))
    return wrapper

async def dump_request(request, **kwargs):
    name = request.match_info.get('name', '')
    args = request.query

    if request.headers.get(aiohttp.hdrs.CONTENT_TYPE, '').startswith('multipart/form-data'):
        mpreader = await request.multipart()
        di = {}
        async for part in mpreader:
            # NOTE: 忽略 filename，忽略重复的 name
            #print(part.filename)
            di[part.name] = await part.text()
        body = json_dumps(di)
    else:
        body = await request.text()

    result = {
        'timestamp': get_strtime(),
        'headers': str(request.headers),
        'request': str(request),
        'url': str(request.url),
        'name': name,
        'body': body,
        'args': str(args),
    }

    pjson(result)

    return result

@json_resp
async def get_handler(request, **kwargs):
    return await dump_request(request, **kwargs)

@json_resp
async def post_handler(request, **kwargs):
    return await dump_request(request, **kwargs)

def signal_handler(signum, frame):
    asyncio.get_event_loop().stop()

def main(argv):
    args = argv[1:]
    signal.signal(signal.SIGINT, signal_handler)
    signal.signal(signal.SIGTERM, signal_handler)

    host = '127.0.0.1'
    port = 12345
    try:
        host = args[0]
        port = int(args[1])
    except IndexError:
        pass

    log('Start on', get_strtime())
    log('version', g_version)

    app = web.Application()
    app.router.add_get('/', get_handler)
    app.router.add_post('/', post_handler)
    app.router.add_get('/{name}', get_handler)
    app.router.add_post('/{name}', post_handler)
    #web.run_app(app, host=host, port=port)
    loop = asyncio.get_event_loop()
    # NOTE: 3.2 后废弃, 不更新的话可用, 更新的话有可能拿不到监听的端口
    coro = loop.create_server(app.make_handler(), host, port)
    server = loop.run_until_complete(coro)
    print('======== Running on http://%s:%s ========' % server.sockets[0].getsockname())
    print('(Press CTRL+C to quit)')
    try:
        loop.run_forever()
    except KeyboardInterrupt:
        pass
    finally:
        server.close()

if __name__ == '__main__':
    sys.exit(main(sys.argv))
