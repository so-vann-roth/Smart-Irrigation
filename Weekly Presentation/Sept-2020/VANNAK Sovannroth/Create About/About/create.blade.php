@extends('admin::layouts.master')
@section('header')
    <strong>Create About</strong>
@endsection
@section('content')
    <form action="{{route('about.store')}}" method="POST" enctype="multipart/form-data">
        @csrf
        <div class="card card-gray">
            <div class="toolbox">
                <button class="btn btn-primary btn-sm btn-oval">
                    <i class="fa fa-save"></i> Save
                </button>
                <a href="{{route('about.index')}}" class="btn btn-warning btn-sm btn-oval">
                    <i class="fa fa-reply"></i> Back
                </a>
            </div>
            <div class="card-block">
                
                <div class="row">
                    <div class="col-sm-7">
                        @component('admin::coms.alert')
                        @endcomponent
                        <div class="form-group row">
                            <label for="title" class="col-sm-3">Title <span class="text-danger">*</span></label>
                            <div class="col-sm-9">
                                <input type="text" class="form-control" id="title" name="title" 
                                    required autofocus value="{{old('title')}}">
                            </div>
                        </div>
                        <div class="form-group row">
                            <label for="url" class="col-sm-3">URL <span class="text-danger">*</span></label>
                            <div class="col-sm-9">
                                <input type="text" class="form-control" id="url" name="url" 
                                    required value="{{old('url')}}">
                            </div>
                        </div>
                        <div class="form-group row">
                        <label for="description" class="col-sm-3">Description</label>
                            <div class="col-sm-9">
                                <textarea name="description" id="" cols="30" rows="4" 
                                    class="form-control">{{old('description')}}</textarea>
                            </div>
                        </div>
                        <div class="form-group row">
                            <label for="icon" class="col-sm-3">Icon</label>
                            <div class="col-sm-9">
                                <input type="text" class="form-control" id="icon" name="icon" 
                                    value="{{old('icon')}}">
                            </div>
                        </div>   
                        <div class="form-group row">
                            <label for="sequence" class="col-sm-3">Sequence</label>
                            <div class="col-sm-9">
                                <input type="text" class="form-control" id="sequence" name="sequence" 
                                    value="1">
                            </div>
                        </div>                                               
                    </div> 
                    <div class="col-sm-5">
                        <div class="form-group row">
                            <label for="photo" class="col-sm-3">Photo</label>
                            <div class="col-sm-9">
                                <input type="file" class="form-control" id="photo" name="photo" 
                                    accept="image/*" onchange="preview(event)">
                                    <div style="margin-top: 9px">
                                        <img src="" alt="" id="img" width="150">
                                    </div>
                            </div>
                        </div>   
                    </div>               
                </div>
            </div>
        </div>
    </form>
@endsection
@section('js')
    <script>
        $(document).ready(function(){
            $('#sidebar-menu li').removeClass('active open');
            $('#sidebar-menu li ul li').removeClass('active');
            $('#menu_about').addClass('active');
        });
        function preview(evt)
        {
            let img = document.getElementById('img');
            img.src = URL.createObjectURL(evt.target.files[0]);
        }
    </script>
@endsection