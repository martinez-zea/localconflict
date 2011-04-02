from django.db import models
from django import forms
from sorl.thumbnail import ImageField

class new(models.Model):
    when = models.DateTimeField(auto_now=True, auto_now_add=True)
    murder = models.CharField(max_length=300)
    dead = models.CharField(max_length = 300)
    team = models.CharField(max_length=10)
    weapon = models.CharField(max_length=100)
    message = models.TextField()
    img = models.ImageField(upload_to="img_up")
    