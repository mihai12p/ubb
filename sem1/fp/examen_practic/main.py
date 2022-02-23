from ui.console import Consola
from service.serv import Service
from repo.repository import InFileGestiune
from domain.validator import Validator

repo = InFileGestiune('data\\melodii.txt')
validator = Validator()
serv = Service(repo, validator)

Consola(serv).showUi()