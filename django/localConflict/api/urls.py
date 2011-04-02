from django.conf.urls.defaults import *
from piston.resource import Resource
from localConflict.api.handlers import newHandler

new_resource = Resource(newHandler)

urlpatterns = patterns('',
    url(r'^new/$', new_resource, {'emitter_format':'xml'}),
)