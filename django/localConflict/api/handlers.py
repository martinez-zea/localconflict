from piston.handler import BaseHandler
from piston.utils import rc
from breaking_news.models import new
from PIL import Image

class newHandler(BaseHandler):
    allowed_methods = ('POST')
    model = new
    
    def create(self, request):
        h = request.REQUEST["headline"]
        b = request.REQUEST["body"]
        
        if('image' in request.FILES):
            im = request.FILES["image"]
            nw = new(headline=h, body=b, image=im)
            
        else:
            nw = new(headline=h, body=b)
                                   
        nw.save()
        return rc.ALL_OK
