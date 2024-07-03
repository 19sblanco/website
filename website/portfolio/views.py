from django.shortcuts import render
from django.http import HttpResponse, JsonResponse
from django.template import loader
from urllib.parse import unquote

# Create your views here.
def index(request):
    context = {}
    return render(request, "portfolio/index.html", context)

def tsp(request):
    context = {}
    return render(request, "portfolio/tsp.html", context)

def tsp_c(request):
    query_string = request.GET.urlencode()
    decoded_string = unquote(query_string)
    point_strings = decoded_string.split('&')
    
    points = []
    for point_str in point_strings:
        x, y = point_str.strip('()=').split(',')
        points.append((int(x), int(y)))
    
    print()
    print(points)
    print()

    # prepare arguments
    arguments = ""
    for p in points:
        arguments += str(p[0]) + "," + str(p[1]) + " "
    print()
    print(arguments)
    print()



