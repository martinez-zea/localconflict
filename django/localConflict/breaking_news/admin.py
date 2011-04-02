from breaking_news.models import *
from django.contrib import admin
from sorl.thumbnail.admin import AdminImageMixin
 
class newAdmin(AdminImageMixin, admin.ModelAdmin):
    list_display = ('when', 'team', 'message', 'weapon')
    list_filter= ['when', 'team', 'weapon']
    date_hierarchy = 'when'
    
admin.site.register(new, newAdmin)