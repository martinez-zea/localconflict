from django.db import models
from django import forms
from sorl.thumbnail import ImageField

class new(models.Model):
    when = models.DateTimeField(auto_now=True, auto_now_add=True)
    headline = models.CharField(max_length=300)
    body = models.TextField()
    image = models.ImageField(upload_to="img_up", blank = True)
    
    def get_absolute_url(self):
        return "/breaking_news/detail/%i/" % self.id
        
    def __unicode__(self):
    	  return self.headline
    