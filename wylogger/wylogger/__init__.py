import requests


__all__ = ["Logger"]
class Logger(object):
    def __init__(self, port: int) -> None:
        self.port = port
        self.available = True

        try:
            requests.get(f"http://127.0.0.1:{port}/available")
        except:
            self.available = False

    def log(self, event, message):
        if self.available:
            try:
                requests.get(f"http://127.0.0.1:{self.port}", {
                        "event": event,
                        "message": message
                    }
                )
            except:
                self.available = False


    def debug(self, message):
        self.log("DEBUG", message)

    def fatal(self, message):
        self.log("FATAL", message)

    def error(self, message):
        self.log("ERROR", message)

    def info(self, message):
        self.log("INFO", message)
    
    def warn(self, message):
        self.log("WARN", message)