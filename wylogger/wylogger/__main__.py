import colorama
import threading
import flask
import logging
import time
import sys
import os


app = flask.Flask(__name__)
app.logger.disabled = True
log = logging.getLogger('werkzeug')
log.disabled = True
data = {"line": 0, "colorized": 0}

def log(event, message):
    data["line"] += 1

    e = event
    t = time.strftime("%H:%M:%S", time.gmtime(time.time()))

    if data["colorized"]:
        if event == "DEBUG":
            event = colorama.Fore.LIGHTGREEN_EX + event + colorama.Style.RESET_ALL
        elif event == "WARN":
            event = colorama.Fore.LIGHTYELLOW_EX + event + colorama.Style.RESET_ALL
        elif event == "FATAL":
            event = colorama.Fore.LIGHTRED_EX + event + colorama.Style.RESET_ALL
        elif event == "INFO":
            event = colorama.Fore.LIGHTCYAN_EX + event + colorama.Style.RESET_ALL
        elif event == "ERROR":
            event = colorama.Fore.LIGHTMAGENTA_EX + event + colorama.Style.RESET_ALL

        t = colorama.Fore.LIGHTBLACK_EX+t+colorama.Style.RESET_ALL
        
    os.system(f"title Wylogger - {e}:{data['line']}")
    print(f"[{t}][{event}] {message}")

@app.route("/")
def event():
    _d = flask.request.args.get("event"), flask.request.args.get("message")

    log(_d[0], _d[1])

    return flask.jsonify({"code": 200}), 200

def hello(port):
    os.system("cls")
    log("INFO", f"logger runned at port {port}")
    log("INFO", f"ctrl+c for exit.")

def main(args):
    colorama.init()
    data["colorized"] = int(args["colorized"]) 
    port = int(args["port"])
    
    threading.Thread(target=hello, args=(port, ), daemon=True).start()
    app.run(port=port)

if __name__ == "__main__":
    default = {
        "port": 4334,
        "colorized": 1
    }

    index = 0
    for arg in sys.argv[1:]:
        index += 1

        if arg.startswith("-"):
            default[arg[1:]] = sys.argv[index+1]

    os.system("title Wylogger")
    main(default)
    