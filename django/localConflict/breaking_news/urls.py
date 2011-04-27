from django.conf.urls.defaults import *
from breaking_news.feeds import LatestEntriesFeed

urlpatterns = patterns('breaking_news.views',
    (r'^$', 'index'),
    (r'^add/$', 'add'),
    (r'^saved/$', 'saved'),
    (r'^detail/(?P<death_id>\d+)/$', 'search'),
    (r'^all/$', 'allNews'),
    (r'^api/', include('localConflict.api.urls')),
    (r'^feed/$', LatestEntriesFeed()),
)