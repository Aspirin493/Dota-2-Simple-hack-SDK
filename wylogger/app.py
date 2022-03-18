import random
import wylogger
import time

log = wylogger.Logger(32454)

while True:
    ev = random.choice(["DEBUG", "FATAL", "INFO", "WARN", "ERROR"])
    log.log(ev, "hello from app #1")

    time.sleep(0.5)
