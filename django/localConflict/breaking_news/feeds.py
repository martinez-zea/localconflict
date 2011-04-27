from django.contrib.syndication.views import Feed
from breaking_news.models import new

class LatestEntriesFeed(Feed):
    title = "Conflicto local -- ultimas noticias"
    link = "/breaking_news/"
    description = "ultimos acontecimientos en conflicto local"
    
    def items(self):
        return new.objects.order_by('when')[:10]
    
    def item_title(self, item):
        return item.headline
    
    def item_description(self, item):
        return item.body
    
#    def item_link(self):
#        return self