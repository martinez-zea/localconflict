from piston.handler import BaseHandler
from piston.utils import rc
from breaking_news.models import new
from PIL import Image

class newHandler(BaseHandler):
    allowed_methods = ('POST')
    model = new
    
    def create(self, request):
        m = request.REQUEST["murder"]
        d = request.REQUEST["dead"]
        t = request.REQUEST["team"]
        w = request.REQUEST["weapon"]
        ms = request.REQUEST["message"]
        im = request.FILES["img"]
        
        nw = new(murder=m, dead=d, team=t, weapon=w, message=ms, img=im)
        nw.save()
        
        return rc.ALL_OK
