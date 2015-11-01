require 'mkmf'
# Load cbuild script to help build C program
load "scripts/cbuild.rb"

#FLASHER = "\"/C/Program Files (x86)/STMicroelectronics/STM32 ST-LINK Utility/ST-LINK Utility/ST-LINK_CLI\" "
FLASHER = trim_string((flasher = ENV['flasher']) ? String.new(flasher):"ST-LINK_CLI")
ELF_TO_HEX = trim_string((elf_to_hex = ENV['elf_to_hex']) ? String.new(elf_to_hex):"arm-none-eabi-objcopy")

# Configuration parameters
config = {
  :verbose      => :no,
  :compiler     => 'arm-none-eabi-gcc',
  :linker       => 'arm-none-eabi-gcc',
# -IC:\Users\user26\CoIDE\workspace\RTOS
  :include_path => ['Drivers/CMSIS/Include',
                    'Drivers/STM32F4xx_HAL_Driver/Inc',
                    'Config',
                    'app'],
  :user_define  => ['STM32F429ZI', 'STM32F429xx'],
  :library_path => '.',
#  :library => ['libusb'],
  :linker_script => 'stm32f429zi_flash.ld',
  :compiler_options => ['-mcpu=cortex-m4 -mthumb -g2 -Wall -O0 -g'],          # Other compiler options
  :linker_options => ['-mcpu=cortex-m4 -mthumb -g2 -O0 -Wl,--gc-sections'],   # Other linker options
  :option_keys  => {:library => '-l',
                    :library_path => '-L',
                    :include_path => '-I',
                    :output_file => '-o',
                    :compile => '-c',
                    :linker_script => '-Wl,-T',
                    :define => '-D'}
}


OUTPUT_PATH = 'build/release/hw/'
namespace :hw do
  ouput_elf = nil
  ouput_hex = nil
  task :prepare_release, [:coproj] do |t, args|
    filenames, coproj = get_all_source_files_in_coproj(args[:coproj])
    file = File.basename(coproj, '.coproj')
    ouput_elf = File.join(OUTPUT_PATH, file + '.elf')
    ouput_hex = File.join(OUTPUT_PATH, file + '.hex')
    dep_list = createCompilationDependencyList(filenames, ['c', '.c++', '.s', 'cpp', 'asm'], '.', '.o')
    dep_list = compile_list(dep_list, '.', OUTPUT_PATH, '.', config)
  #  p dep_list
    link_all(getDependers(dep_list), ouput_elf, config)

    file ouput_hex => ouput_elf do |n|
      if(program_available?(ELF_TO_HEX) == nil)
        puts "Error: Cannot find #{ELF_TO_HEX} program to turn ELF to HEX."
        exit
      end
      puts "converting #{n.prerequisites[0]} to hex..."
      sys_cli "#{ELF_TO_HEX} -O ihex #{n.prerequisites[0]} #{n.name}"
    end
  end
#  CLEAN.include('build/release/hw') if File.exist? 'build/release/hw'

  desc 'Build hardware release code'
  task :release, [:coproj] => :prepare_release do |t, args|
  #  p Rake.application.tasks

    Rake::Task[ouput_elf].invoke(args)
  #  sh "cp #{OUTPUT_FILE} ."
  end

  desc 'Flash program and run test'
  task :flash, [:coproj] => :prepare_release do |t, args|
    Rake::Task[ouput_hex].invoke(args)
    if(program_available?(FLASHER) == nil)
      puts "Error: Cannot find #{FLASHER} program to flash ARM processor."
      exit
    end
    sys_cli FLASHER + " -P #{ouput_hex} -V while_programming -Rst -Run"
  end

  desc "Just duplicating .gitignore"
  task :ignore do
    src = ".gitignore"
    target = ".gitignoreXXX"
    if !up_to_date?(target, src)
      p "duplicating .gitignore"
      sh "cp #{src} #{target}"
    else
      p "already have the latest copy..."
    end
  end
end
