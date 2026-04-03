import logging

# Standard Logger for DLI Python SDK
# Matches dli::Logger capability in C++

class Logger:
    _logger = logging.getLogger("dli")
    _logger.setLevel(logging.DEBUG)
    
    _ch = logging.StreamHandler()
    _formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
    _ch.setFormatter(_formatter)
    _logger.addHandler(_ch)

    @staticmethod
    def debug(msg: str):
        Logger._logger.debug(msg)

    @staticmethod
    def info(msg: str):
        Logger._logger.info(msg)

    @staticmethod
    def warn(msg: str):
        Logger._logger.warning(msg)

    @staticmethod
    def error(msg: str):
        Logger._logger.error(msg)
