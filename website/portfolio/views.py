from django.shortcuts import render
from django.http import HttpResponse
from django.template import loader

# Create your views here.
def index(request):
    context = {}
    return render(request, "portfolio/index.html", context)

def tsp(request):
    context = {}
    return render(request, "portfolio/tsp.html", context)

