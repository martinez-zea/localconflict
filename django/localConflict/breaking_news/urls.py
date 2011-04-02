from django.conf.urls.defaults import *

urlpatterns = patterns('breaking_news.views',
    (r'^$', 'index'),
    (r'^add/$', 'add'),
    (r'^saved/$', 'saved'),
    (r'^search/(?P<death_id>\d+)/$', 'search'),
    (r'^api/', include('localConflict.api.urls')),
)