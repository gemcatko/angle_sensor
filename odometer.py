aktualny_angle = 1         # n step angle
last_angle = 359      # n-1 angle
delta_angle = 0   #  last_angle - angle
sum_of_angles = 0    #sum of all angles from start of program

def get_angle_from_sensor():
    #nacitaj uhol z konzoli alebo z hocikade
    return aktualny_angle

#needed to get initial angle to have initial state!!!! this need to be uncomenteed if loop is inplemented!!!!!
#last_angle = get_angle_from_sensor()


get_angle_from_sensor()
delta_angle = (last_angle - aktualny_angle)
if abs(delta_angle) <= 180:
    delta_angle_naozajsna_kladny_smer = delta_angle
    sum_of_angles = sum_of_angles + delta_angle_naozajsna_kladny_smer
    print("Hybe sa kladne",delta_angle_naozajsna_kladny_smer)

if  abs(delta_angle) > 180:
    delta_angle_naozajsna_zaporny_smer = 360 - abs(delta_angle)
    sum_of_angles = sum_of_angles - delta_angle_naozajsna_zaporny_smer
    print("Hybe sa zaporne",delta_angle_naozajsna_zaporny_smer)