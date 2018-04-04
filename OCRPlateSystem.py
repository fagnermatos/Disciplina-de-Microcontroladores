from openalpr import Alpr
import pygame, sys
import pygame.camera
import RPi.GPIO
import time
import requests

gpio = RPi.GPIO
gpio.cleanup()
gpio.setmode(gpio.BOARD)
# Configure pinOut
gpio.setup(11, gpio.OUT)
gpio.output(11, gpio.LOW)
gpio.setup(13, gpio.OUT)
gpio.output(13, gpio.LOW)

# Configure pinInput
gpio.setup(16, gpio.IN, pull_up_down = gpio.PUD_DOWN)
gpio.add_event_detect(16,gpio.FALLING)

plates = []

def getPlates():
    r = requests.get('http://192.168.0.8:1234/plates', auth=('',''))
    if r.status_code is 200:
        plts = r.text
        plts = plts.split('\n')
        plts.pop()
        return list(plts)

def takePhoto():
    try:
        game.init()
        pygame.camera.init()
        cam = pygame.camera.Camera("/dev/video0", (640,480))
        cam.start()
        image = cam.get_image()
        cam.stop
        filename = 'car1.jpg'
        pygame.image.save(image, filename)
    except:
        print 'Erro ao capturar foto'
    print 'taking photo'
    
def detectPlate():
    alpr = Alpr("eu","/path/to/openalpr.conf", "/home/pi/openalpr/runtime_data")
    if not alpr.is_loaded():
        print "Erro! Verifique se a lib Openalpr foi instalada corretamente."
        sys.exit(1)
    alpr.set_top_n(20)
    alpr.set_default_region("md")
    results = alpr.recognize_file("cart.jpg")
    plate = ""
    acuraccy = ""
    for plate in results['results']:
        for candidate in plate['candidates']:
            plate = candidate['plate']
            acuraccy = candidate['confidence']
            break
    alpr.unload()
    return plate

while (True):
    if gpio.event_detected(16):
        print 'Event detected'
        plates = getPlates()
        takePhoto()
        plate = detectPlate()
        print plate
	detected = False
        for plt in plates:
            if plt == plate:
		detected = True
                gpio.output(11, gpio.HIGH)
		time.sleep(5)
		gpio.output(11, gpio.LOW)
	if not detected:
	     gpio.output(13, gpio.HIGH)
	     time.sleep(5)
	     gpio.output(13, gpio.LOW)
