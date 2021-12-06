from ui.console import Console
from repo.repo import FirmeFileRepo
from service.srv import FirmeSrv

repo = FirmeFileRepo('data/firme.txt')
valid = None
serv = FirmeSrv(repo, valid)

ui = Console(serv)
ui.showUi()
