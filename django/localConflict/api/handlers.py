from piston.handler import BaseHandler
from breaking_news.models import new
from PIL import Image

class newHandler(BaseHandler):
    model = new