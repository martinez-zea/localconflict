from breaking_news.models import *
from django.shortcuts import render_to_response, get_object_or_404
from django.http import HttpResponseRedirect, HttpResponse
from django.template import RequestContext

def index(request):
    
    n_image = new.objects.filter(image__startswith='img_up').order_by('-when')[:3]
    n_text = new.objects.filter(image__startswith='').order_by('-when')[:12]
   
    return render_to_response('breaking_news/index.html', {'with_img' : n_image,
                                                            'without_img': n_text,}
                                                            , context_instance=RequestContext(request))
                                                            
def allNews(request):
    all_news = new.objects.all().order_by('-when')
    
    return render_to_response('breaking_news/all.html', 
                              {'all_news' : all_news}, 
                              context_instance=RequestContext(request))

def add(request):
    return HttpResponse("@ add")

def saved(request):
    return HttpResponse("saved!")

def search(request, death_id):
    n = get_object_or_404(new, pk=death_id)
    return render_to_response('breaking_news/detail.html', {'new':n}, context_instance=RequestContext(request))

