#ifndef UDES_H
#define UDES_H
//Data pour un fichier SVG

float udes[700][2] = {{-98.50,124.05},{-98.59,121.58},{-98.78,119.12},{-99.44,116.76},{-101.49,115.95},{-103.00,117.84},{-103.71,120.20},{-104.14,122.63},{-104.43,125.08},{-104.61,127.54},{-104.71,130.01},{-104.74,132.48},{-104.70,134.94},{-104.57,137.41},{-104.34,139.87},{-104.02,142.31},{-103.61,144.75},{-103.12,147.17},{-102.35,145.84},{-101.58,143.49},{-100.89,141.12},{-100.28,138.73},{-99.75,136.32},{-99.31,133.89},{-98.96,131.45},{-98.71,128.99},{-98.56,126.53},{-98.50,124.06},{-131.70,110.63},{-132.65,112.91},{-133.51,115.22},{-134.29,117.56},{-134.98,119.93},{-135.58,122.33},{-136.11,124.74},{-136.55,127.17},{-136.92,129.61},{-137.22,132.06},{-137.45,134.51},{-137.62,136.98},{-137.72,139.44},{-137.76,141.91},{-137.71,144.38},{-137.56,146.84},{-137.34,149.30},{-137.05,151.75},{-136.64,154.19},{-136.04,156.58},{-135.17,158.89},{-134.14,161.13},{-132.94,163.28},{-131.37,165.18},{-129.38,166.64},{-127.10,167.56},{-124.67,167.97},{-122.20,167.95},{-119.78,167.49},{-117.48,166.62},{-115.34,165.38},{-113.40,163.86},{-111.63,162.14},{-111.11,159.98},{-111.45,157.53},{-111.70,155.08},{-111.86,152.62},{-111.93,150.15},{-111.86,147.68},{-111.68,145.22},{-111.46,142.76},{-111.20,140.31},{-110.91,137.86},{-110.58,135.41},{-110.20,132.97},{-109.77,130.54},{-109.29,128.12},{-108.76,125.71},{-108.16,123.32},{-107.49,120.94},{-106.74,118.59},{-105.91,116.26},{-104.97,113.98},{-103.87,111.77},{-102.55,109.69},{-100.91,107.85},{-98.80,106.61},{-96.39,106.62},{-94.80,108.45},{-94.11,110.81},{-93.80,113.26},{-93.71,115.72},{-93.75,118.19},{-93.90,120.65},{-94.14,123.11},{-94.47,125.56},{-94.87,127.99},{-95.32,130.42},{-95.83,132.83},{-96.39,135.24},{-97.01,137.63},{-97.68,140.00},{-98.41,142.36},{-99.20,144.70},{-100.03,147.02},{-100.93,149.32},{-101.87,151.60},{-101.31,153.96},{-100.51,156.30},{-99.60,158.59},{-98.58,160.84},{-97.43,163.02},{-96.13,165.12},{-94.70,167.13},{-93.07,168.98},{-91.19,170.58},{-89.08,171.85},{-86.77,172.70},{-84.33,173.08},{-81.89,172.86},{-79.77,171.62},{-77.55,170.78},{-76.15,172.70},{-76.79,175.03},{-78.35,176.94},{-80.20,178.57},{-82.19,180.03},{-84.32,181.27},{-86.59,182.25},{-88.95,182.94},{-91.39,183.35},{-93.85,183.48},{-96.29,183.16},{-98.58,182.24},{-100.64,180.90},{-102.49,179.25},{-104.13,177.42},{-105.57,175.41},{-106.81,173.28},{-107.88,171.06},{-108.80,168.76},{-109.57,166.42},{-110.86,167.48},{-112.39,169.42},{-114.01,171.28},{-115.73,173.05},{-117.56,174.71},{-119.50,176.23},{-121.57,177.58},{-123.75,178.73},{-126.04,179.66},{-128.41,180.32},{-130.85,180.70},{-133.32,180.79},{-135.77,180.54},{-138.14,179.88},{-140.33,178.74},{-142.22,177.16},{-143.75,175.23},{-144.95,173.07},{-145.85,170.78},{-146.51,168.40},{-146.98,165.98},{-147.29,163.53},{-147.47,161.07},{-147.55,158.60},{-147.54,156.13},{-147.45,153.66},{-147.30,151.20},{-147.08,148.74},{-146.81,146.29},{-146.47,143.84},{-146.08,141.41},{-145.64,138.98},{-145.14,136.56},{-144.61,134.15},{-144.03,131.75},{-143.41,129.36},{-142.75,126.98},{-142.05,124.62},{-141.30,122.26},{-140.50,119.93},{-139.64,117.61},{-138.72,115.33},{-137.71,113.07},{-136.62,110.86},{-135.41,108.71},{-133.88,106.80},{-131.57,106.01},{-130.44,107.60},{-52.66,166.28},{-52.45,168.74},{-52.27,171.20},{-52.52,173.62},{-54.72,174.26},{-55.91,172.33},{-56.18,169.87},{-56.40,167.42},{-56.62,164.96},{-57.84,163.55},{-60.13,164.38},{-61.56,166.35},{-62.01,168.76},{-61.80,171.21},{-60.83,173.47},{-59.27,175.38},{-57.35,176.93},{-55.25,178.22},{-53.00,179.22},{-50.62,179.87},{-48.16,180.12},{-45.71,179.88},{-43.34,179.20},{-41.08,178.21},{-38.93,177.00},{-37.04,175.64},{-39.05,174.20},{-41.02,172.72},{-42.98,171.21},{-44.94,169.71},{-46.93,168.26},{-48.97,166.86},{-51.07,165.56},{-57.20,122.22},{-55.89,124.20},{-55.58,126.64},{-55.42,129.10},{-55.25,131.57},{-55.08,134.03},{-54.90,136.49},{-54.72,138.95},{-54.54,141.41},{-54.36,143.88},{-54.18,146.34},{-53.99,148.80},{-53.81,151.26},{-53.62,153.72},{-53.04,155.60},{-50.63,155.05},{-48.18,154.78},{-45.72,154.88},{-43.30,155.38},{-40.98,156.20},{-38.72,157.20},{-36.58,158.42},{-34.56,159.84},{-32.58,161.32},{-30.62,162.82},{-28.65,164.31},{-26.95,164.46},{-25.98,162.19},{-25.30,159.82},{-24.94,157.38},{-24.90,154.92},{-25.30,152.48},{-26.03,150.12},{-26.97,147.84},{-28.05,145.63},{-29.25,143.47},{-30.53,141.36},{-31.88,139.29},{-33.29,137.26},{-34.75,135.28},{-36.27,133.33},{-37.85,131.43},{-39.47,129.58},{-41.15,127.76},{-42.88,126.00},{-44.67,124.30},{-46.51,122.66},{-48.41,121.08},{-50.36,119.57},{-52.36,118.13},{-54.41,116.75},{-56.51,115.45},{-58.66,114.24},{-60.88,113.15},{-63.16,112.22},{-65.52,111.48},{-67.93,110.99},{-70.39,110.80},{-72.84,111.09},{-75.17,111.90},{-77.32,113.10},{-79.29,114.58},{-81.08,116.27},{-82.70,118.14},{-84.20,120.10},{-85.55,122.16},{-86.87,124.22},{-89.14,123.82},{-89.31,121.59},{-87.95,119.53},{-86.44,117.58},{-84.82,115.72},{-83.13,113.91},{-81.39,112.16},{-79.62,110.45},{-77.78,108.80},{-75.82,107.29},{-73.77,105.92},{-71.63,104.69},{-69.40,103.64},{-67.07,102.83},{-64.66,102.32},{-62.20,102.16},{-59.74,102.34},{-57.31,102.79},{-54.93,103.43},{-52.59,104.23},{-50.30,105.15},{-48.06,106.19},{-45.88,107.34},{-43.76,108.60},{-41.69,109.96},{-39.69,111.39},{-37.73,112.90},{-35.83,114.47},{-33.98,116.10},{-32.18,117.79},{-30.44,119.54},{-28.76,121.35},{-27.16,123.23},{-25.67,125.20},{-24.29,127.25},{-23.03,129.37},{-21.88,131.55},{-20.84,133.79},{-19.93,136.08},{-19.18,138.43},{-18.58,140.83},{-18.15,143.26},{-17.88,145.71},{-17.76,148.18},{-17.84,150.64},{-18.18,153.09},{-18.74,155.49},{-19.48,157.84},{-20.36,160.15},{-21.37,162.40},{-22.47,164.61},{-23.66,166.77},{-22.39,168.16},{-20.07,168.98},{-17.63,169.35},{-15.28,168.77},{-13.19,167.45},{-10.91,167.29},{-10.84,169.64},{-12.09,171.75},{-13.71,173.61},{-15.50,175.31},{-17.40,176.88},{-19.45,178.26},{-21.66,179.35},{-24.02,180.07},{-26.47,180.31},{-28.91,179.95},{-31.23,179.12},{-33.31,178.95},{-35.11,180.63},{-36.99,182.23},{-38.94,183.74},{-40.97,185.14},{-43.08,186.43},{-45.26,187.58},{-47.52,188.58},{-49.83,189.43},{-52.21,190.10},{-54.63,190.60},{-57.07,190.92},{-59.54,191.05},{-62.00,190.95},{-64.42,190.47},{-66.67,189.47},{-68.56,187.90},{-69.94,185.86},{-70.75,183.54},{-71.10,181.10},{-71.10,178.63},{-70.75,176.19},{-70.11,173.81},{-69.24,171.50},{-68.19,169.26},{-66.99,167.10},{-65.65,165.04},{-64.13,163.09},{-62.44,161.29},{-60.59,159.66},{-58.59,158.22},{-57.40,156.47},{-57.63,154.02},{-57.85,151.56},{-58.07,149.10},{-58.30,146.64},{-58.52,144.18},{-58.74,141.72},{-58.97,139.27},{-59.19,136.81},{-59.42,134.35},{-59.64,131.89},{-59.86,129.43},{-60.69,127.22},{-61.07,124.92},{-59.55,123.00},{31.58,113.70},{31.84,111.29},{30.16,109.59},{27.81,108.88},{25.35,108.86},{22.91,109.26},{20.53,109.91},{18.21,110.75},{15.94,111.71},{13.71,112.78},{11.55,113.96},{9.44,115.26},{7.42,116.66},{5.48,118.19},{3.69,119.89},{2.22,121.86},{1.70,124.23},{2.53,126.54},{4.18,128.36},{6.14,129.86},{8.25,131.14},{10.46,132.22},{12.59,133.47},{14.59,134.93},{16.30,136.69},{17.23,138.95},{17.08,141.41},{16.18,143.69},{14.75,145.70},{13.04,147.48},{11.13,149.05},{9.23,150.62},{7.35,152.22},{5.64,154.00},{4.26,156.04},{3.33,158.32},{2.97,160.76},{3.30,163.19},{4.44,165.37},{6.17,167.12},{8.26,168.41},{10.62,169.13},{13.08,169.26},{15.54,169.04},{17.95,168.56},{20.31,167.81},{22.56,166.80},{24.68,165.54},{26.66,164.07},{28.53,162.47},{30.36,160.81},{32.14,159.09},{33.87,157.34},{35.71,155.72},{37.63,156.83},{37.45,159.22},{36.21,161.34},{34.68,163.28},{33.04,165.12},{31.31,166.88},{29.50,168.57},{27.64,170.19},{25.73,171.75},{23.76,173.23},{21.71,174.61},{19.60,175.90},{17.44,177.09},{15.24,178.19},{12.99,179.21},{10.69,180.11},{8.34,180.85},{5.93,181.40},{3.48,181.71},{1.02,181.72},{-1.43,181.38},{-3.77,180.63},{-5.91,179.40},{-7.69,177.70},{-8.93,175.58},{-9.53,173.19},{-9.55,170.72},{-9.18,168.29},{-8.44,165.93},{-7.39,163.70},{-6.10,161.60},{-4.66,159.59},{-3.07,157.71},{-1.32,155.98},{0.48,154.28},{2.24,152.55},{3.97,150.79},{5.50,148.86},{6.23,146.54},{5.05,144.44},{3.05,142.99},{0.87,141.84},{-1.41,140.90},{-3.66,139.89},{-5.69,138.50},{-7.46,136.78},{-8.68,134.65},{-9.12,132.23},{-8.89,129.78},{-8.16,127.42},{-7.04,125.23},{-5.65,123.19},{-4.07,121.30},{-2.34,119.53},{-0.53,117.85},{1.36,116.26},{3.31,114.75},{5.33,113.33},{7.41,112.00},{9.54,110.75},{11.71,109.59},{13.91,108.47},{16.13,107.39},{18.37,106.35},{20.63,105.35},{22.90,104.40},{25.20,103.49},{27.52,102.64},{29.85,101.84},{32.21,101.11},{34.60,100.50},{37.04,100.10},{39.50,100.12},{41.88,100.73},{43.85,102.19},{44.92,104.39},{44.80,106.83},{43.57,108.95},{41.77,110.63},{39.72,112.00},{37.57,113.22},{35.34,114.28},{32.95,114.78},{92.15,119.02},{91.53,116.94},{92.24,114.62},{91.25,112.43},{89.10,111.26},{86.70,110.69},{84.24,110.64},{81.79,110.90},{79.38,111.42},{77.02,112.17},{74.74,113.12},{72.54,114.23},{70.41,115.47},{68.37,116.87},{66.47,118.44},{64.76,120.22},{63.31,122.21},{62.19,124.41},{61.47,126.77},{61.95,129.17},{62.99,131.40},{64.43,133.40},{66.15,135.18},{68.01,136.80},{69.97,138.29},{72.04,139.65},{74.18,140.87},{76.34,142.07},{78.49,143.28},{80.64,144.50},{82.78,145.72},{84.87,147.04},{86.84,148.51},{88.69,150.15},{90.37,151.95},{91.82,153.95},{92.85,156.19},{93.30,158.61},{93.11,161.06},{92.34,163.40},{91.12,165.55},{89.62,167.50},{88.02,169.38},{86.32,171.17},{84.52,172.86},{82.74,174.56},{84.88,174.68},{87.29,174.13},{89.62,173.33},{91.89,172.35},{94.10,171.25},{96.26,170.05},{98.37,168.78},{100.46,167.47},{102.03,168.86},{100.62,170.68},{98.71,172.24},{96.65,173.61},{94.51,174.82},{92.30,175.93},{90.05,176.94},{87.76,177.88},{85.46,178.75},{83.13,179.57},{80.79,180.35},{78.43,181.09},{76.06,181.78},{73.68,182.42},{71.28,183.01},{68.87,183.55},{66.45,184.03},{64.02,184.45},{61.57,184.80},{59.12,185.07},{56.66,185.27},{54.19,185.38},{51.73,185.39},{49.26,185.30},{46.80,185.05},{44.38,184.62},{42.01,183.92},{39.78,182.87},{37.85,181.34},{36.47,179.31},{35.80,176.94},{36.02,174.53},{37.50,172.56},{39.28,170.86},{41.15,169.24},{43.13,167.78},{45.44,167.93},{47.61,169.10},{49.73,170.36},{51.90,171.54},{54.12,172.63},{56.37,173.64},{58.64,174.60},{60.96,175.45},{63.33,176.14},{65.74,176.64},{68.19,176.94},{70.66,177.04},{73.12,176.85},{75.50,176.22},{77.68,175.08},{79.51,173.43},{80.97,171.44},{82.06,169.23},{82.61,166.83},{82.51,164.37},{81.73,162.04},{80.35,160.00},{78.59,158.27},{76.66,156.73},{74.62,155.34},{72.49,154.10},{70.30,152.97},{68.10,151.85},{65.91,150.71},{63.72,149.57},{61.54,148.41},{59.43,147.14},{57.42,145.70},{55.54,144.10},{53.82,142.33},{52.38,140.33},{51.37,138.08},{50.91,135.66},{51.00,133.20},{51.55,130.80},{52.47,128.51},{53.68,126.36},{55.10,124.35},{56.69,122.45},{58.39,120.66},{60.18,118.96},{62.03,117.33},{63.95,115.78},{65.93,114.30},{67.96,112.91},{70.05,111.59},{72.19,110.36},{74.37,109.21},{76.60,108.14},{78.86,107.15},{81.16,106.25},{83.49,105.46},{85.87,104.79},{88.28,104.28},{90.73,103.96},{93.20,103.90},{95.65,104.12},{98.02,104.79},{100.02,106.21},{101.06,108.41},{101.08,110.87},{100.30,113.20},{98.91,115.23},{97.15,116.96},{95.16,118.42}};

#endif