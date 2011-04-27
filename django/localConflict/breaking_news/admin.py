from breaking_news.models import *
from django.contrib import admin
from sorl.thumbnail.admin import AdminImageMixin
 
class newAdmin(AdminImageMixin, admin.ModelAdmin):
    list_display = ('when', 'headline', 'body', 'image')
    list_filter= ['when',]
    date_hierarchy = 'when'
    
admin.site.register(new, newAdmin)